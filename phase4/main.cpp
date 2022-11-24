#include <netinet/in.h>
#include "Node.h"

int main(){
	Server s(50, 4000, 10, 100);
	s.start();
	return 0;
}
