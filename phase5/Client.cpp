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
	std::cout << "client: " << guid << " successfully connected" << std::endl;
	connected = true;
	return;
}

void Client::reconnect(){
	if ((client_fd = connect(sockfd, (struct sockaddr*)&address, sizeof(address)))< 0){
		std::cout << "client: " << guid << "failed to connect" << std::endl;
		//exit(1);
		return;
	}
	std::cout << "client: " << guid << "successfully connected" << std::endl;
	connected = true;
	return;

}

void Client::send_text(const std::string &msg)
{
	if (connected){
	send(sockfd,msg.c_str(),msg.size(), 0);
	}else {
		std::cout << "client: " << guid << " Not Connected" << std::endl;
	}
}

void Client::send_msg(const Message &msg)
{
	if (connected){
	std::string msg_str;
	msg_str = msg.type + "-" + std::to_string(msg.sguid) + "-" + std::to_string(msg.tguid) + "-" + msg.msg + "~";
	send(sockfd,msg_str.c_str(),msg_str.size(), 0);
	}else{
		std::cout << "client: " << guid << " Not Connected" << std::endl;
	}
}



