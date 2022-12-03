#ifndef SERVER_H
#define SERVER_H
#include <sys/socket.h>
#include <string>
#include <mutex>
#include "Node.h"
#include "NodeList.h"
#include "MessageIDBuffer.h"
#include "Interests.h"


class Server: public Node{
	public:
		Server(int g, int p, int sq, int bs);
		void start();
		void start_interests(Interests *interests);
		void start_node(NodeList *nodes, Interests *interests);
		void start_server_online(bool *server_online);
		void start_friends(NodeList *friends,std::mutex *mtx, MessageIDBuffer *mbuffer);
		static void handle_client_node(int connfd, int server_buffer_size, NodeList *nodes);
		static void handle_client_node_interests(int connfd, int server_buffer_size, NodeList *nodes,Interests *interests);
		static void handle_client(int connfd, int server_buffer_size);
		static void handle_client_interests(int connfd, int server_buffer_size,Interests *interests);
		static void handle_client_friends(int connfd, int server_buffer_size, NodeList *friends, std::mutex *mtx, MessageIDBuffer *mbuffer);
	private:
		int server_queue;
		int server_buffer_size;
		
};

#endif
