#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <arpa/inet.h>
#include <iostream>
#include "Node.h"

class Node{
	public: 
		Node() = delete;
		Node(int p);
		void startServer(int server_queue, int server_buffer_size);
		void connectTo(const char *addr);
		void disconnect();
		void send(const std::string &msg);
	
	private:
		int port;
		bool connected;
		int recvr_socket;
		int sendr_socket;
		struct sockaddr_in *self_addr_in;
		struct sockaddr_in *target_addr_in;
		std::string targetAddr;
};

#endif

Node::Node(int p){
	port = p;
	connected = false;

	if ((recvr_socket = socket(AF_INET, SOCK_STREAM, 0))<0){
		perror("Node Unable to Open Reciever Socket\n");
		exit(1);
	}
	if ((sendr_socket = socket(AF_INET, SOCK_STREAM, 0))<0){
		perror("Node Unable to Open Sender Socket\n");
		exit(1);
	}

	memset((char *)self_addr_in, 0, sizeof(*self_addr_in));
	self_addr_in->sin_family = AF_INET;
	self_addr_in->sin_port = htons(port);
	self_addr_in->sin_addr.s_addr = htonl(INADDR_ANY);
	
	if (bind(recvr_socket, (struct sockaddr *)self_addr_in, sizeof(self_addr_in))<0){
		perror("Binding of Node Sercer TCP Socket Failed\n");
		exit(1);
	}
	std::cout << "Node Server TCP Socket Successfully Binded" << std::endl;

	memset((char *)target_addr_in, 0, sizeof(*target_addr_in));
	
}

void Node::startServer(int server_queue, int server_buffer_size){

	if (listen(recvr_socket, server_queue)<){
		perror("Node Server TCP Socket Failed to Listen\n");
		exit(1);
	}
	std::cout << "Node Server TCP Socket Now Listening" << std::endl;

	int connfd;
	struct sockaddr_in client_addr;
	socklen_t alen;
	int valread;
	char server_buffer[server_buffer_size] = {0};
	while(1){
		if((connfd = accept(recvr_socket, (struct sockaddr *)&client_addr, &alen))<0){
			perror("Node Server Unable to Accept Client\n");
			exit(1);
		}
		std::cout << "" << std::endl;
	}
	
}
void Node::connectTo(const char *addr);
	//set connected to true
void Node::disconnect();
	//check if connected, if false, fail the function
	//clean and reset the thing
void Node::send(const std::string &msg);
	//check if connected
