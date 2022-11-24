#include <netinet/in.h>
#include "Node.h"
int main(){
	Server s(50, 8000, 10, 100);
	s.start();
	return 0;
}
