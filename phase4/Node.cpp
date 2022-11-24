#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <arpa/inet.h>
#include <iostream>
#include "Node.h"

Node::Node(int g, const char *addr, int p):
	guid(g), 
	port(p)
{
	
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0))<0){
		perror("Node Unable to Open Socket\n");
		exit(1);
	}
	std::cout<< "Node TCP Socket Successfully Opened" << std::endl;
	
	memset((char *)address, 0, sizeof(*address));
	address->sin_family = AF_INET;
	address->sin_port = htons(port);

	if (inet_pton(AF_INET, addr, &address->sin_addr)<=0){
		perror("Node Recieved an Invalid Address\n");
		exit(1);
	}	
}

Server::Server(int g, int p, int sq, int bs):
	Node(g, "127.0.0.1", p),
	server_queue(sq),
	server_buffer_size(bs)
{
	if (bind(sockfd, (struct sockaddr *)address, sizeof(*address))<0){
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

void Client::send_msg(const char *msg)
{
	if ((client_fd = connect(sockfd, (struct sockaddr*)address, sizeof(*address)))< 0){
		perror("Node Client Recieved an Invalid Address\n");
		exit(1);
	}
	send(sockfd,msg,strlen(msg),0);
	close(client_fd);

}



