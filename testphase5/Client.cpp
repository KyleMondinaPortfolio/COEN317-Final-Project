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
	if ((client_fd = connect(sockfd, (struct sockaddr*)&address, sizeof(address)))< 0){
		perror("Node Client Recieved an Invalid Address\n");
		exit(1);
	}
}

void Client::send_msg(const std::string &msg)
{
	send(sockfd,msg.c_str(),msg.size(), 0);
}

void Client::send_msg(const Message &msg)
{
	std::string msg_str;
	msg_str+=msg.sguid;
	msg_str+="-";
	msg_str+=msg.tguid;
	msg_str+="-";
	msg_str+=msg.type;
	msg_str+="-";
	msg_str+=msg.msg;
	send(sockfd,msg_str.c_str(),msg_str.size(), 0);
}



