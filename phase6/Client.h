#ifndef CLIENT_H
#define CLIENT_H
#include <sys/socket.h>
#include <string>
#include "Node.h"
#include "Message.h"

class Client: public Node{
	public: 
		Client(int g, const char *addr, int p);
		void send_text(std::string msg);
		void send_msg(Message msg);
	private:
		int client_fd;
		bool connected = false;
};

#endif
