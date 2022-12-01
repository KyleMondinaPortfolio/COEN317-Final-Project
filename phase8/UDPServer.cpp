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

