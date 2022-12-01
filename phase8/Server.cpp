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
#include "Server.h"
#include "Message.h"
#include "NodeList.h"

//utility function to parse a string and return a message

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

void Server::handle_client_node(int connfd, int server_buffer_size, NodeList *nodes){
	int client_socket = connfd;
	int valread;
	char server_buffer[server_buffer_size] = {0};

	while(1){
		//clear the buffer
		memset(server_buffer,' ',server_buffer_size);

		//read the message from client socket
		if((valread = read(client_socket,server_buffer,server_buffer_size))<0){
			std::cout << "server failed to read from client: " << client_socket << std::endl;
		}
		if(valread == 0){
			break;
		}

		//parse the message
		std::string recieved_message(server_buffer);
		Message parsed_msg = parse_msg(recieved_message);

		if (parsed_msg.mtype() == "post"){
			std::cout << "Message Type: " << parsed_msg.mtype() << std::endl;
			std::cout << "Sending Post to All Nodes" << std::endl;
			nodes->send_to_all(recieved_message);
		}else if (parsed_msg.mtype() == "dm"){
			std::cout << "Message Type: " << parsed_msg.mtype() << std::endl;
			std::cout << "sguid: " << parsed_msg.msguid()<< " sent a message to: " << 
			parsed_msg.mtguid()<< " saying: " << parsed_msg.mmsg() << std::endl;
			nodes->send_to(parsed_msg.mtguid(),parsed_msg);
		}else if (parsed_msg.mtype() == "ping"){
			//No Action Necessary, Message Sent was a Failure Detection
			//return;
		}
		std::cout << "Recieved Message: " << recieved_message << std::endl;
	}
}

void Server::handle_client(int connfd, int server_buffer_size){
	int client_socket = connfd;
	int valread;
	char server_buffer[server_buffer_size] = {0};

	while(1){
		//clear the buffer
		memset(server_buffer,' ',server_buffer_size);

		//read the message from client socket
		if((valread = read(client_socket,server_buffer,server_buffer_size))<0){
			std::cout << "server failed to read from client: " << client_socket << std::endl;
		}
		if(valread == 0){
			break;
		}

		//parse the message
		std::string recieved_message(server_buffer);
		Message parsed_msg = parse_msg(recieved_message);
		if (parsed_msg.mtype() == "ping"){
			//No Action Necessary, Message Sent was a Failure Detection
		}
		std::cout << "Message Type: " << parsed_msg.mtype() << std::endl;
		std::cout << "Recieved Message: " << recieved_message << std::endl;
	}
}

void Server::start()
{
	int connfd;
	struct sockaddr_in clientAddr;
	socklen_t alen;

	while (1){
		if ((connfd = accept(sockfd, (struct sockaddr *)&clientAddr, &alen))<0){
			perror("Node Server Unable to Accept Client\n");
			exit(1);
		}
		std::cout << "Node Server Accepted Client " << connfd << std::endl;

		//dispatch a thread to process the request
		std::thread t(handle_client,connfd,server_buffer_size);
		t.detach();
	}	
}

void Server::start_node(NodeList *nodes)
{
	int connfd;
	struct sockaddr_in clientAddr;
	socklen_t alen;
	while (1){
		if ((connfd = accept(sockfd, (struct sockaddr *)&clientAddr, &alen))<0){
			perror("Node Server Unable to Accept Client\n");
			exit(1);
		}
		std::cout << "Node Server Accepted Client " << connfd << std::endl;

		std::thread t(handle_client_node,connfd,server_buffer_size,nodes);
		t.detach();
		
	}	
}

void Server::start_server_online(bool *server_online)
{
	//Add NodeList as a Parameter
	int connfd;
	struct sockaddr_in clientAddr;
	socklen_t alen;
	while (1){
		std::cout << "Server Ready to Accept Again" << std::endl;
		std::cout << "Code Before the Accept" << std::endl;
		if ((connfd = accept(sockfd, (struct sockaddr *)&clientAddr, &alen))<0){
			std::cout << "Accept Failed" << std::endl;
			perror("Node Server Unable to Accept Client\n");
			exit(1);
		}
		std::cout << "Code After Accept" << std::endl;
		std::cout << "Node Server Accepted Client " << connfd << std::endl;
		if (*server_online == true){
			std::cout << "Central Server is Online, using COSN Handler" << std::endl;
			//handle_client(connfd,server_buffer_size);
			std::thread t(handle_client,connfd,server_buffer_size);
			t.detach();
		}else{
			std::cout << "Central Server is Offline, using P2P Handler" << std::endl;
		}
	}	
}

