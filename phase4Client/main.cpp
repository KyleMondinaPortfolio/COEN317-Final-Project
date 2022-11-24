#include <netinet/in.h>
#include "Node.h"

int main(){
	Client c(51,"35.93.97.89", 8000);
	c.send_msg("hi\n");
	return 0;
}
