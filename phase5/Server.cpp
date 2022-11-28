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
Message parse_msg(const std::string &msg_str){

	int first = msg_str.find("-");
	int second = msg_str.find("-",first+1);
	int third = msg_str.find("-",second+1);

	std::string type = msg_str.substr(0,first);
	int sguid = std::stoi(msg_str.substr(first+1,second-first-1));
	int tguid = std::stoi(msg_str.substr(second+1,third-second-1));
	std::string message = msg_str.substr(third+1,msg_str.find("~")-third);
	return Message(sguid,tguid,type,message);
}

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

void Server::nodes_handle_client(int connfd, int server_buffer_size, const NodeList &nodes){
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
		std::string recieved_message(server_buffer);
		std::cout << "Recieved Message: " << recieved_message << std::endl;

		//parse the message
		Message parsed_msg = parse_msg(recieved_message);
		std::cout << "Message Type: " << parsed_msg.type << std::endl;
		if (parsed_msg.type == "post"){
			std::cout << "Sending Post to All Nodes" << std::endl;
			nodes.send_to_all(recieved_message);
		}else if (parsed_msg.type == "dm"){
			std::cout << "sguid: " << parsed_msg.sguid<< " sent a message to: " << 
			<< parsed_msg.tguid<< " saying: " << parsed_msg.msg << std::endl;
		}
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
		std::string recieved_message(server_buffer);
		std::cout << "Recieved Message: " << recieved_message << std::endl;

		//parse the message
		std::string delimeter = "-";
		std::string type = recieved_message.substr(0,recieved_message.find(delimeter));
		std::cout << "Message Type: " << type << std::endl;
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

void Server::start (const NodeList &nodes)
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

		std::thread t(nodes_handle_client,connfd,server_buffer_size,nodes);
		t.detach();
		
	}	
}
