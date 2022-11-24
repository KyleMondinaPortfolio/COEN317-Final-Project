#ifndef NODE_H
#define NODE_H
#include <sys/socket.h>
#include <string>

class Node{
	public: 
		Node() = delete;
		Node(int port);
		void startServer(int server_queue, int server_buffer_size);
		void connectTo(const char *addr);
		void disconnect();
		void send(const std::string &msg);
	
	private:
		int port;
		int recvr_socket;
		int sendr_socket;
		struct sockaddr_in self_addr_in;
		struct sockaddr_in target_addr_in;
		std::string targetAddr;
		bool connected;
};

#endif
