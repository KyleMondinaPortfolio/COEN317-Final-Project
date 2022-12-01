#ifndef UDPSERVER_H
#define UDPSERVER_H
#include <sys/socket.h>
#include <string>
#include <mutex>
#include "Node.h"
#include "UDPNode.h"
#include "NodeList.h"
#include "MessageIDBuffer.h"


class UDPServer: public UDPNode{
	public:
		UDPServer(int g, int p, int bs);
		void start();
		//void start_friends(NodeList *friends,std::mutex *mtx, MessageIDBuffer *mbuffer);
		//static void handle_client_friends(int connfd, int server_buffer_size, NodeList *friends, std::mutex *mtx, MessageIDBuffer *mbuffer);
	private:
		int server_buffer_size;
		
};

#endif
