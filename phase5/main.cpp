#include <netinet/in.h>
#include "Server.h"
#include "Client.h"

int main(){
	Server s(50, 8000, 10, 100);
	s.start();
	return 0;
}
