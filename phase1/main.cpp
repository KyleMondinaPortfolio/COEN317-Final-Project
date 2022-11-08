#include <string>
#include <iostream>
#include "User.h"
#include "Users.h"
using namespace std;

int main(){

	User jo1("Jo1", "12.2.3.4", 500);
	jo1.display();
	cout<<endl;
	User jo2("Jo2", "12.2.3.4", 500);
	User jo3("Jo3", "12.2.3.4", 500);
	User jo4("Jo4", "12.2.3.4", 500);
	User jo5("Jo5", "12.2.3.4", 500);

	cout << " Displaying the UserS " << endl;
	Users students;
	students.addUser(&jo1);
	students.addUser(&jo2);
	students.addUser(&jo3);
	students.addUser(&jo4);
	students.addUser(&jo5);
	students.displayUsers();
	return 0;
}
