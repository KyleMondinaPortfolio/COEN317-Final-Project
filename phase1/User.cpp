#include "User.h"
using namespace std;

void User::display() const{
	cout << name << " ";
	cout << addr << " ";
	cout << port << endl;
	return;
}
