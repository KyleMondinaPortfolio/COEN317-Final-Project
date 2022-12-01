#include <netinet/in.h>
#include <iostream>
#include "Server.h"
#include "Client.h"
#include <fstream>
#include <chrono>
#include <thread>
#include <mutex>
#include "Message.h"
#include "NodeList.h"
#include "MessageIDBuffer.h"
#include "UDPServer.h"

void user_interface(NodeList *friends,Client *server, bool *server_online){
	while(1){
		//blocking parsing user input
		std::string user_input;
		std::getline(std::cin,user_input);
		std::cout << "User Input: " << std::endl;
		std::cout << user_input << std::endl;
		std::cout << "Central Server State: " << *server_online << std::endl;
		if (*server_online == true){
			std::cout << "Sending User Input to Central Server" << std::endl;
			Message msg = parse_msg(user_input);
			server->send_msg(msg);
		}else{
			std::cout << "Multicasting User Input to P2P Network" << std::endl;
		}
	}
}

int main(){

	int guid = 0;
	int server_type = 0;

	if (server_type == 0){
		Client c1(1, "54.149.66.46", 8000);
		//Client c1(1, "34.208.184.118", 7000);
		//Client c1(1, "54.202.116.197", 8000);
		Message msg("post",0,3,"test multicast");
		c1.send_msg(msg);
		return 0;
	}
	else if (server_type == 1){
		//Node Client Code
		bool server_online = false;
		Client central_server_heartbeat(1, "54.149.66.46", 9000);
		Client central_server(1, "54.149.66.46", 8000);
		Server self_main(guid,8000,100,1000);
		Server self_friends(guid,7000,100,1000);

		NodeList friends("./FriendsOf1.txt");
		

		//Failure Detector for Central Server
		std::mutex monitor_mtx;
		std::thread t1(&Client::monitor_failure,&central_server_heartbeat,true,3,&monitor_mtx,&server_online);

		//Main Listener
		std::thread t2(&Server::start, &self_main);
	
		//P2P Listener
		MessageIDBuffer mbuffer;	
		std::mutex buffer_mtx; 
		std::thread t4(&Server::start_friends, &self_friends,&friends,&buffer_mtx,&mbuffer);

		//User Interface
		std::thread t3(user_interface,&friends,&central_server,&server_online);

		t1.join();
		t2.join();
		t3.join();
		return 0;

	}else if (server_type == 2){
		//Central Server Code
		NodeList nodes("./Users.txt");
		nodes.show();
		Server self_main(1,8000,100,1000);
		Server self_heart(1,9000,100,1000);

		//for port 8000
		//Main Server
		std::thread t1(&Server::start_node,&self_main,&nodes);
		//Nodes Failure Detector
		std::thread t2(&NodeList::monitor_failures,&nodes,false,3);

		//for port 9000
		//heart beat server: used for client to check the status of the server
		std::thread t3(&Server::start,&self_heart);
		
		t1.join();
		t2.join();
		t3.join();
		return 0;
	}else{
		std::cout << "Server Type Not Specified" <<std::endl;
		UDPServer userver(1,7000,1000);
		userver.start();
		return 0;
	}
	
}

