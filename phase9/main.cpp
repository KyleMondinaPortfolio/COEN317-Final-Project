#include <netinet/in.h>
#include <iostream>
#include <cstdlib>
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
#include "UDPClient.h"
#include "UDPNodeList.h"
#include "TimeStamp.h"
#include "Interests.h"
	
int guid = 0;
int server_type = 0;

void user_interface(UDPNodeList *friends,Client *server, bool *server_online, TimeStamp *ts, std::mutex *mtx, MessageIDBuffer *mbuffer){

	while(1){
		//blocking parsing user input
	
		std::string message_type;
		std::string user_message;
		int user_id = guid;
		std::string stid;
		int target_id;
		int message_id = rand();

		std::cout << "----User Interface-----" << std::endl; 

		std::cout << "Enter Type of Message You Want" << std::endl; 
		std::getline(std::cin,message_type);

		std::cout << "Enter Target's ID" << std::endl; 
		std::getline(std::cin,stid);
		target_id = std::stoi(stid);

		std::cout << "Enter Message You Want to Broadcast Over the Network" << std::endl; 
		std::getline(std::cin,user_message);

		int time_stamp;
		ts->send(&time_stamp,mtx);
		
		Message formatted_message(message_type,user_id,target_id,time_stamp,message_id,user_message);
		std::cout << "Message that will be sent" <<std::endl;
		std::cout << format_msg(formatted_message) << std::endl;
		std::cout << "Message ID: " << formatted_message.mid() <<std::endl;
		mbuffer->add(message_id);
		std::cout << "Message Time Stamp " << formatted_message.mtimestamp() <<std::endl;

		if (*server_online == true){
			std::cout << "Server is Online" << std::endl;
			std::cout << "Sending User Input to Central Server" << std::endl;
			
			server->send_text(format_msg(formatted_message));
		}else{
			std::cout << "Server is Offline" << std::endl;
			std::cout << "Multicasting User Input to P2P Network" << std::endl;
			//add a time stamp send
			friends->send_to_all_except(guid,formatted_message);
		}
	}
}

int main(){

	if (server_type == 0){
		Client c1(1, "54.149.66.46", 8000);
		//UDPClient c1(1, "34.208.184.118", 7000);
		//UDPClient c1(1, "54.202.116.197", 8000);
		//UDPClient c1(1, "54.149.66.46", 7000);
		//UDPClient c1(1, "54.202.92.56", 7000);
		//UDPClient c1(1, "35.92.125.224", 7000);
		Message msg("post",0,0,0,0,"test multicast");
		
		c1.send_msg(msg);
		return 0;
	}
	else if (server_type == 1){
		//Node Client Code
		bool server_online = false;
		Client central_server_heartbeat(1, "54.149.66.46", 9000);
		Client central_server(1, "54.149.66.46", 8000);
		Server self_main(guid,8000,100,1000);
		UDPServer self_friends(guid,7000,1000);

		std::string file_name("./FriendsOf");
		file_name.append(std::to_string(guid));
		file_name.append(".txt");
		std::cout << file_name << std::endl;
		UDPNodeList friends(file_name.c_str());
		//UDPNodeList friends("./FriendsOf3.txt");
		//UDPNodeList friends("./FriendsOf4.txt");
		
		//Failure Detector for Central Server
		std::mutex monitor_mtx;
		std::thread t1(&Client::monitor_failure,&central_server_heartbeat,true,3,&monitor_mtx,&server_online);

		//Main Listener
		std::thread t2(&Server::start, &self_main);
	
		MessageIDBuffer mbuffer;	

		//User Interface
		TimeStamp ts;
		std::mutex tsmtx;
		std::thread t3(user_interface,&friends,&central_server,&server_online,&ts,&tsmtx,&mbuffer);

		//P2P Listener
		std::mutex buffer_mtx; 
		self_friends.start_friends(&friends,&buffer_mtx,&mbuffer,&ts,&tsmtx);

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
		//UDPNodeList friends("./FriendsOf1.txt");
		//std::cout << "Server Type Not Specified" <<std::endl;
		//std::mutex tsmtx;
		//int value;
		//TimeStamp ts;
		//ts.send(&value,&tsmtx);
		//std::cout << "Time Stamp Value shoudl be 1, Actual: " << value << std::endl;	
		//ts.send(&value,&tsmtx);
		//std::cout << "Time Stamp Value shoudl be 2, Actual: " << value << std::endl;	
		//ts.recieve(&value,&tsmtx,5); 
		//std::cout << "Time Stamp Value shoudl be 6, Actual: " << value << std::endl;	
		
		//std::string example("1+cookies,2+cookies|1+cookies,2+cookies|1+cookies,2+cookies");
		//Interests interest(example);
		//interest.show();
		//interest.format();
		//std::string msg("post-1-2-cookies are the best~");
		//Message message = parse_msg(msg);
		//std::cout << message.mmsg() << std::endl; 
		
		//std::string reform = format_msg(message);
		//std::cout << reform << std::endl;
		
		return 0;
	}
	
}

