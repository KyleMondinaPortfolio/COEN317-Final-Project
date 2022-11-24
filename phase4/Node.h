#ifndef NODE_H
#define NODE_H
#include <sys/socket.h>
#include <string>

class Node{
	public:
		Node(int g, const char *addr, int p);
	protected:
		struct sockaddr_in address;
		int sockfd;			
	private:
		int guid;
		int port;
};

class Server: public Node{
	public:
		Server(int g, int p, int sq, int bs);
		void start();
	private:
		int server_queue;
		int server_buffer_size;
		
};

class Client: public Node{
	public: 
		Client(int g, const char *addr, int p):Node(g, addr, p){}
		void send_msg(const char *msg);
	private:
		int client_fd;
};

#endif
