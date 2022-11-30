#include <netinet/in.h>
#include <iostream>
#include "Server.h"
#include "Client.h"
#include <fstream>
#include <thread>
#include "Message.h"
#include "NodeList.h"

//Message(int sg, int tg, const std::string &t, const std::string &m):
//Client c1(1, "54.149.66.46", 8000);
//Client c3(3, "34.208.184.118", 8000);
;

int main(){
	
	Client c1(1, "54.149.66.46", 8000);
	Message msg("post",0,3,"count dankula");
	c1.send_msg(msg);


	/*
	//For Server Instance 1
	NodeList nodes("./Users.txt");
	nodes.show();
	Server s(2,8000,100,1000);
	std::thread t1(&Server::node_start,&s,&nodes);
	std::thread t2(&NodeList::monitor_failures,&nodes);
	t1.join();
	t2.join();
	*/

	/*
	//For Instance 2
	Server s(2,8000,100,1000);
	s.start();
	*/

	/*
	//For Instance 3
	Server s(3,8000,100,1000);
	s.start();
	*/

	return 0;
}


