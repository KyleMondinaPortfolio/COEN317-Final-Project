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

		std::string raw_recieved_message(server_buffer);
		std::string recieved_message = raw_recieved_message.substr(0,raw_recieved_message.find("~")+1);
		Message parsed_msg = parse_msg(recieved_message);

		std::cout << "Recieved Message" << recieved_message << std::endl;
		//print the thing, later parse it

		if (parsed_msg.mtype() == "post"){
			//check if the message has been sent to you already, if it has, discard it else add to buffer and propogate it
			//message id will be stored in tguid
			mtx->lock();
			int msg_id = parsed_msg.mtguid();
			bool is_duplicate = mbuffer->contains(msg_id);
			if (!is_duplicate){
				mbuffer->add(msg_id);
				std::cout << "Message New, Gossip throughout the P2P Network" << std::endl;
				std::cout << "Recieved Message: " << recieved_message << std::endl;
				friends->send_to_all_except(parsed_msg.msguid(),recieved_message);
			}else{
				std::cout << "Duplicate Message Recieved" << std::endl;
				std::cout << "Recieved Message: " << recieved_message << std::endl;
			} 
			mtx->unlock();
		}

	}
}



