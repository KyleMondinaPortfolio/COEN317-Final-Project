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

void user_interface(Client *server, bool *server_online){
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
		//Client c1(1, "34.208.184.118", 8000);
		//Client c1(1, "54.202.116.197", 8000);
		Message msg("post",0,3,"what is going on");
		c1.send_msg(msg);
		return 0;
	}
	else if (server_type == 1){
		//Node Client Code
		bool server_online = false;
		Client central_server(1, "54.149.66.46", 9000);
		Server self_main(guid,8000,100,1000);
		Server self_heart(guid,9000,100,1000);

		//Failure Detector for Central Server
		std::mutex monitor_mtx;
		std::thread t1(&Client::monitor_failure,&central_server,true,3,&monitor_mtx,&server_online);

		//Background Listening Process
		//For Failure Detection
		std::thread t2(&Server::start_server_online, &self_heart, &server_online);
		//Main Listener
		std::thread t3(&Server::start, &self_main);

		t1.join();
		t2.join();
		t3.join();
		return 0;

	}else if (server_type == 2){
		//Central Server Code
		NodeList nodes("./Users.txt");
		NodeList heart_beats("./Detect.txt");
		nodes.show();
		heart_beats.show();
	
		Server self_main(1,8000,100,1000);
		Server self_heart(1,9000,100,1000);

		//for port 8000
		std::thread t1(&Server::start_node,&self_main,&nodes);
		//for port 9000
		std::thread t2(&Server::start,&self_heart);

		//Nodes Failure Detector
		std::thread t3(&NodeList::monitor_failures,&heart_beats,false,3);
		
		t1.join();
		t2.join();
		t3.join();
		return 0;
	}else{
		std::cout << "Server Type Not Specified" <<std::endl;
		return 0;
	}
	
}

