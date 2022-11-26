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

#endif
