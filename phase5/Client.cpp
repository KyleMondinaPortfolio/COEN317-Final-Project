#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <arpa/inet.h>
#include <iostream>
#include "Client.h"

void Client::send_msg(const char *msg)
{
	if ((client_fd = connect(sockfd, (struct sockaddr*)&address, sizeof(address)))< 0){
		perror("Node Client Recieved an Invalid Address\n");
		exit(1);
	}
	send(sockfd,msg,strlen(msg),0);
	close(client_fd);

}



