#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <arpa/inet.h>
#include <sstream>
#include <iostream>
#include "Client.h"
#include "Message.h"

Client::Client(int g, const char *addr, int p):
	Node(g, addr, p)
{	
	std::cout << "client: " << guid << " attempting to connect" << std::endl;
	if ((client_fd = connect(sockfd, (struct sockaddr*)&address, sizeof(address)))< 0){
		std::cout << "client: " << guid << "failed to connect" << std::endl;
		return;
	}
	connected = true;
	std::cout << "client: " << guid << " successfully connected" << std::endl;
}

void Client::send_text(std::string msg) 
{
	if (connected){
		send(sockfd,msg.c_str(),msg.size(), 0);
	}else{
		std::cout << "failed to send text" << " client: " << guid << "is offline" << std::endl;
	}
		
}

void Client::send_msg(Message msg) 
{
	if (connected){
		std::string msg_str = format_msg(msg);
		send(sockfd,msg_str.c_str(),msg_str.size(), 0);
	}else{
		std::cout << "failed to send message" << " client: " << guid << "is offline" << std::endl;
	}
	
}



