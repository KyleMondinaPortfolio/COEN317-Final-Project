#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <arpa/inet.h>
#include <iostream>
#include "Server.h"
#include "NodeList.h"

Server::Server(int g, int p, int sq, int bs):
	Node(g, "0.0.0.0", p),
	server_queue(sq),
	server_buffer_size(bs)
{
	if (bind(sockfd, (struct sockaddr *)&address, sizeof(address))<0){
		perror("Server TCP Socket Binding Failed");
		exit(1);
	}
	std::cout<< "Server TCP Socket Successfully Binded" << std::endl;

	if (listen(sockfd,server_queue)<0){
		perror("Server Listening Failed\n");
		exit(1);
	}

	std::cout << "Server Now Listening To TCP Socket: " << sockfd << std::endl;	
}

void Server::start()
{
	int connfd;
	struct sockaddr_in clientAddr;
	socklen_t alen;
	int valread;
	char server_buffer[server_buffer_size] = {0};
	while (1){
		if ((connfd = accept(sockfd, (struct sockaddr *)&clientAddr, &alen))<0){
			perror("Node Server Unable to Accept Client\n");
			exit(1);
		}
		std::cout << "Node Server Accepted Client " << connfd << std::endl;
		//clear the buffer
		memset(server_buffer,' ',server_buffer_size);
		if((valread = read(connfd,server_buffer,server_buffer_size))<0){
			std::cout << "server failed to read from client: " << connfd << std::endl;
		}
		std::string test(server_buffer);
		std::cout << test << std::endl;
	}	
}

void Server::start(const NodeList &nodes)
{
	int connfd;
	struct sockaddr_in clientAddr;
	socklen_t alen;
	int valread;
	char server_buffer[server_buffer_size] = {0};
	while (1){
		if ((connfd = accept(sockfd, (struct sockaddr *)&clientAddr, &alen))<0){
			perror("Node Server Unable to Accept Client\n");
			exit(1);
		}
		std::cout << "Node Server Accepted Client " << connfd << std::endl;
		//clear the buffer
		memset(server_buffer,' ',server_buffer_size);
		if((valread = read(connfd,server_buffer,server_buffer_size))<0){
			std::cout << "server failed to read from client: " << connfd << std::endl;
		}
		std::string message(server_buffer);
		std::cout << "Recieved Message: " << message << std::endl;
		//parsing the message
		std::string delimeter = "-";
		std::string type = message.substr(message.find(delimeter));
		std::cout << "Message Type: " << type << std::endl;
		
	}	
}
