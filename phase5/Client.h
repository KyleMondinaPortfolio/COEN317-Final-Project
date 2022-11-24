#ifndef CLIENT_H
#define CLIENT_H
#include <sys/socket.h>
#include <string>
#include "Node.h"

class Client: public Node{
	public: 
		Client(int g, const char *addr, int p):Node(g, addr, p){}
		void send_msg(const char *msg);
	private:
		int client_fd;
};

#endif
