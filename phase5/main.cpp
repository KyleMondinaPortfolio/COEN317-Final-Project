#include <netinet/in.h>
#include <iostream>
#include "Server.h"
#include "Client.h"
#include <fstream>
#include "Message.h"
#include "NodeList.h"

int main(){
	//server Code
	NodeList nodes("./Users.txt");
	nodes.show();
	//Server s(50,8000,100,1000);	
	//s.start();
	/*
	Client c(50, "127.0.0.1", 8000);
	Message m(50,50,"post","cookies are the best");
	c.send_msg(m);
	*/
	//Client c(50, "127.0.0.1", 8000);
	return 0;
}


