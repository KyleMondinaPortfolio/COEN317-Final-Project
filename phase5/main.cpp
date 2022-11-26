#include <netinet/in.h>
#include <iostream>
#include "Server.h"
#include "Client.h"
#include <fstream>
#include "Message.h"
#include "NodeList.h"


//Message(int sg, int tg, const std::string &t, const std::string &m):

int main(){
	//server Code
	//NodeList nodes("./Users.txt");
	//nodes.show();
	//Server s(50,8000,100,1000);	
	//s.start();
	/*
	Client c(50, "127.0.0.1", 8000);
	Message m(50,50,"post","cookies are the best");
	c.send_msg(m);
	*/
	//Client c(50, "127.0.0.1", 8000);
	Client c1(3, "34.208.184.118", 8000);
	//Client c2(2, "34.208.184.118", 8000);
	//Client c3(3, "54.202.92.56", 8000);
	//c1.send_msg("hi 1 from local test");
	Message msg(3,4,"post","I am at SCU");
	c1.send_msg(msg);
	//c2.send_msg("hi 2 from local test");
	//c3.send_msg("hi 3 from local test");
	return 0;
}


