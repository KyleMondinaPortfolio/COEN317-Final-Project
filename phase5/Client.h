#ifndef CLIENT_H
#define CLIENT_H
#include <sys/socket.h>
#include <string>
#include "Node.h"
#include "Message.h"

class Client: public Node{
	public: 
		Client(int g, const char *addr, int p);
		void reconnect();
		//void reconnect();
		bool isOnline() const {return connected;}
		void send_text(const std::string &msg);
		void send_msg(const Message &msg);
	private:
		int client_fd;
		bool connected = false;
};

#endif
