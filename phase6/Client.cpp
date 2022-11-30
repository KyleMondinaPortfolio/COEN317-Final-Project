#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sstream>
#include <string>
#include <iostream>
#include "Client.h"
#include "Message.h"

Client::Client(int g, const char *addr, int p):
	Node(g, addr, p)
{	
	try_connect();
}

void Client::try_connect()
{
	std::cout << "Attempting to Connect To Client" << guid  << std::endl;
	if ((client_fd = connect(sockfd, (struct sockaddr*)&address, sizeof(address)))< 0){
		perror("Problem Occured While Attempting to Connect to Client"); 
		std::cout << "Failed to Connect to Client: " << guid << std::endl;
		if (errno == ENOTSOCK || errno == EBADF){
			restart_port();	
		}else if (errno == EISCONN){
			connected = true;
		}
		return;
	}
	connected = true;
	std::cout << "Successfully Connected To Client: " << guid << std::endl;
}

void Client::send_text(std::string msg) 
{
	if (connected){
		std::cout << "Attempting to Send Text to Client: " << guid  << std::endl;
		if((send(sockfd,msg.c_str(),msg.size(), 0)) < MSG_NOSIGNAL){
			std::cout << "Client: " << guid << " Failed to Send Text " << std::endl;
			if (errno == ECONNRESET){
				std::cout << "ECONNRESET SIGNAL" << std::endl;
			}else if (errno == ENOTCONN){
				std::cout << "ENOTCONN SIGNAL" << std::endl;
			}else if (errno == EPIPE){
				std::cout << "EPIPE SIGNAL" << std::endl;
			}
			connected = false;
			close(sockfd);
		}
		std::cout << "Successfully Sent Text To Client: " << guid << std::endl;
		
	}else{
		std::cout << "Fialed to Send Text To Client: " << guid << std::endl;
		std::cout << "Client: " << guid << " Is Offline" << std::endl;
	}
		
}

void Client::send_msg(Message msg) 
{
	if (connected){
		std::cout << "Attempting to Send Message to Client: " << guid  << std::endl;

		std::string msg_str = format_msg(msg);
		if((send(sockfd,msg_str.c_str(),msg_str.size(), MSG_NOSIGNAL)) < 0){
			std::cout << "Client: " << guid << " Failed to Send Message " << std::endl;
			if (errno == ECONNRESET){
				std::cout << "ECONNRESET SIGNAL" << std::endl;
			}else if (errno == ENOTCONN){
				std::cout << "ENOTCONN SIGNAL" << std::endl;
			}else if (errno == EPIPE){
				std::cout << "EPIPE SIGNAL" << std::endl;
			}
			connected = false;
			close(sockfd);
		}
		std::cout << "Successfully Sent Message To Client: " << guid << std::endl;
		
	}else{
		std::cout << "Fialed to Send Message To Client: " << guid << std::endl;
		std::cout << "Client: " << guid << " Is Offline" << std::endl;
	}
}



