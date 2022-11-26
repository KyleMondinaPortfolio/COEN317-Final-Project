#include <netinet/in.h>
#include <iostream>
#include "Server.h"
#include "Client.h"
#include <fstream>
#include "Message.h"

int main(){
	//Client c(50, "127.0.0.1", 8000);
	//Message m(50,50,"post","cookies are the best");
	//c.send_msg(m);
	Server s(50,8000, 10, 100);
	s.start();
	return 0;
}


