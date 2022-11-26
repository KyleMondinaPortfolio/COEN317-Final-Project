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
	private:
		int server_queue;
		int server_buffer_size;
		
};

#endif
