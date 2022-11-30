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
;

int main(){
	
	Client c1(1, "54.149.66.46", 8000);
	Message msg("post",0,3,"count dankula");
	c1.send_msg(msg);
	
	/*
	//For Server 1
	Client c1(1, "34.208.184.118", 8000);
	Message msg(3,4,"type","I am at SCU");
	c1.send_msg(msg);
	*/

	/*
	//For Server 2
	NodeList nodes("./Users1.txt");
	nodes.show();
	Server s(2,8000,100,1000);
	s.start(nodes);
	*/

	/*
	//For Server 3
	Server s(3,8000,100,1000);
	s.start();
	*/

	//std::string type = recieved_message.substr(0,recieved_message.find(delimeter));
	return 0;
}


