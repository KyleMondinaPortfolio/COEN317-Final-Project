#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>
#include "Node.h"


Node::Node(int p){
	port = p;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0))<0){
		perror("Node Unable to Open Socket\n");
		exit(1);
	}
	std::cout << "Node TCP Socket Successfully Opened" << std::endl;	
	memset((char *)nodeAddr, 0, sizeof(*nodeAddr));
	nodeAddr->sin_family = AF_INET;
	nodeAddr->sin_port = htons(port);
}

void Node::startServer(int server_queue, int server_buffer_size){
	nodeAddr->sin_addr.s_addr = htonl(INADDR_ANY);
	
	if (bind(sockfd, (struct sockaddr *)nodeAddr, sizeof(*nodeAddr))<0){
		perror("Binding of Node Server TCP Socket Failed\n");
		exit(1);
	}	

	std::cout << "Node Server Successfully Binded" << std::endl;	
	
	if (listen(sockfd,server_queue)<0){
		perror("Node Server Listening Failed\n");
		exit(1);
	}

	std::cout << "Node Server Now Listening To TCP Socket" << std::endl;	
	
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
	
		valread = read(connfd,server_buffer,server_buffer_size);
		std::cout << server_buffer << std::endl;
	}	
}


void Node::connectTo(const char *addr){
	if (inet_pton(AF_INET, addr, &nodeAddr->sin_addr)<=0){
		perror("Node Client Recieved an Invalid Address\n");
		exit(1);
	}	
	int client_fd;
	if ((client_fd = connect(sockfd, (struct sockaddr*)nodeAddr, sizeof(*nodeAddr)))< 0){
		perror("Node Client Recieved an Invalid Address\n");
		exit(1);
	}
	char *test_msg = "Testing";
	send(sockfd,test_msg,strlen(test_msg),0);
	close(client_fd);

}
