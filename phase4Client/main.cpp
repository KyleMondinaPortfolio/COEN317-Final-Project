#include <netinet/in.h>
#include "Node.h"

int main(){
	Client c(51,"127.0.0.1", 4000);
	
	c.send_msg("hi");
	return 0;
}
