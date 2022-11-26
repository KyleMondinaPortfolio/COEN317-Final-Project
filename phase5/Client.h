#ifndef CLIENT_H
#define CLIENT_H
#include <sys/socket.h>
#include <string>
#include "Node.h"
#include "Message.h"

class Client: public Node{
	public: 
		Client(int g, const char *addr, int p);
		void send_text(const std::string &msg);
		void send_msg(const Message &msg);
	private:
};

#endif
