#ifndef SERVER_H
#define SERVER_H
#include <sys/socket.h>
#include <string>
#include "Node.h"
#include "NodeList.h"

class Server: public Node{
	public:
		Server(int g, int p, int sq, int bs);
		void start();
		void start(const NodeList &nodes);
		static void nodes_handle_client(int connfd, int server_buffer_size, const NodeList &nodes);
		static void handle_client(int connfd, int server_buffer_size);
	private:
		int server_queue;
		int server_buffer_size;
		
};

#endif
