#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <arpa/inet.h>
#include <iostream>
#include "Server.h"

Server::Server(int g, int p, int sq, int bs):
	Node(g, "127.0.0.1", p),
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
		if((valread = read(connfd,server_buffer,server_buffer_size))<0){
			std::cout << "server failed to read from client: " << connfd << std::endl;
		}
		std::cout << server_buffer << std::endl;
	}	
}

