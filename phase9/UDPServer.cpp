#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string>
#include <iostream>
#include <thread>
#include <mutex>
#include "UDPNode.h"
#include "UDPServer.h"
#include "Message.h"
#include "NodeList.h"
#include "MessageIDBuffer.h"


UDPServer::UDPServer(int g, int p, int bs):
	UDPNode(g, "0.0.0.0", p),
	server_buffer_size(bs)
{

	if (bind(sockfd, (const struct sockaddr *)&address, sizeof(address))<0){
		perror("Server TCP Socket Binding Failed");
		exit(1);
	}

	std::cout<< "Server TCP Socket Successfully Binded" << std::endl;

}

void UDPServer::start(){
	while (1){
		int n;
		struct sockaddr_in clientAddr;
		socklen_t alen;
		char server_buffer[server_buffer_size] = {0};
		n = recvfrom(sockfd, (char *)server_buffer, server_buffer_size, MSG_WAITALL, (struct sockaddr*)&clientAddr, &alen); 
		if (n<0){std::cout << "n got < 0" <<std::endl;}
		std::string raw_recieved_message(server_buffer);
		std::string recieved_message = raw_recieved_message.substr(0,raw_recieved_message.find("~")+1);
		std::cout << "Recieved Message" << recieved_message << std::endl;
		//print the thing, later parse it
	}
}

void UDPServer::start_friends(UDPNodeList *friends, std::mutex *mtx,MessageIDBuffer *mbuffer){
	while (1){
		int n;
		struct sockaddr_in clientAddr;
		socklen_t alen;
		char server_buffer[server_buffer_size] = {0};

		n = recvfrom(sockfd, (char *)server_buffer, server_buffer_size, MSG_WAITALL, (struct sockaddr*)&clientAddr, &alen); 
		if (n<0){std::cout << "n got < 0" <<std::endl;}

		std::string raw_recieved_message(server_buffer);
		std::string recieved_message = raw_recieved_message.substr(0,raw_recieved_message.find("~")+1);
		Message parsed_msg = parse_msg(recieved_message);

		std::cout << "Recieved Message" << recieved_message << std::endl;
		std::cout << "Message ID: " << parsed_msg.mid() << std::endl;
		
		std::string type = parsed_msg.mtype();
		int r_sguid = parsed_msg.msguid();
		int r_tguid = parsed_msg.mtguid();
		int r_ts = parsed_msg.mtimestamp();
		int r_mid = parsed_msg.mid();
		std::string mmsg = parsed_msg.mmsg();
		
		//print the thing, later parse it

		if (type == "post"){
			//check if the message has been sent to you already, if it has, discard it else add to buffer and propogate it
			//message id will be stored in tguid
			mtx->lock();

			bool is_duplicate = mbuffer->contains(r_mid);
			if (!is_duplicate){
				mbuffer->add(r_mid);
				std::cout << "Message New, Gossip throughout the P2P Network" << std::endl;
				std::cout << "Recieved Message: " << recieved_message << std::endl;

				int ts = 3;
				//update the message's source
				Message new_message(type,guid,r_tguid,ts,r_mid,mmsg);
				std::string str_new_message = format_msg(new_message); 
				friends->send_to_all_except(r_sguid,str_new_message);
			}else{
				std::cout << "Duplicate Message Recieved" << std::endl;
				std::cout << "Recieved Message: " << recieved_message << std::endl;
			} 

			mtx->unlock();
		}

	}
}





