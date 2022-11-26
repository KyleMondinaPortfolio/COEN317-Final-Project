#include <netinet/in.h>
#include <iostream>
#include "Server.h"
#include "Client.h"
#include <fstream>
#include "Message.h"
#include "NodeList.h"


//Message(int sg, int tg, const std::string &t, const std::string &m):
//Client c1(1, "54.149.66.46", 8000);
//Client c3(3, "34.208.184.118", 8000);

int main(){
	
	/*
	NodeList nodes("./Users.txt");
	nodes.show();
	Server s(1,8000,100,1000);
	s.start(nodes);
	
	*/

	Client c1(1, "54.149.66.46", 8000);
	Message msg(3,4,"post","I am at SCU");
	c1.send_msg(msg);
	//c2.send_msg("hi 2 from local test");
	//c3.send_msg("hi 3 from local test");
	return 0;
}


