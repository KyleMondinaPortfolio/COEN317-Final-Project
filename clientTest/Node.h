#ifndef NODE_H
#define NODE_H
#include <sys/socket.h>

class Node{
	public: 
		Node() = delete;
		Node(int);
		void startServer(int server_queue, int server_buffer_size);
		void connectTo(const char *addr);
	
	private:
		int port;
		int sockfd;
		struct sockaddr_in *nodeAddr;
};

#endif
