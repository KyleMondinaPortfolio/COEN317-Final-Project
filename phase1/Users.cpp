#include "Users.h"
using namespace std;

void Users::displayUsers(){
	for (auto it = users.begin(); it != users.end(); ++it){
		(*it).display();
	}
}
void Users::displayUserNames(){
	for (auto it = users.begin(); it != users.end(); ++it){
		cout << (*it).getName() << endl;
	}
	cout << endl;
}
