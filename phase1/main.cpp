#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "User.h"
#include "Users.h"
using namespace std;

//functions that initializes the list from a file

Users createUsers(const string &fileName);

int main(){

	Users users = createUsers("./Users.txt");
	//assumed that users opened correctly
	cout << "Chat Program Running" << endl
	     << "Commands: " << endl
	     << "d: display users" << endl 
	     << "e: exit program" << endl; 
	while(1){
		string command;
		if (cin >> command){
			if (command == "d"){
				cout << "users: " << endl;
				users.displayUsers();
			}
			else if (command == "e"){
				cout << "exiting program" << endl;
				break;
			}
			else{
				cout << "invalid command" << endl;
			}
		}
		
	}
	cout << "program exited" << endl;
	users.displayUserNames();
	users.displayUsers();

	return 0;
}

Users createUsers(const string &fileName){

	ifstream usersFile(fileName);
	if (usersFile){
		cout << "successfully opened file" << endl;
		
	}else{
		cout << "unable to open file" << endl;
	}
	Users users;
	string line, word;
	while (getline(usersFile,line)){
		istringstream fileLine(line);
		string name, addr, port;
		fileLine >> name;
		fileLine >> addr;
		fileLine >> port;
		User user(name,addr,port);	
		users.addUser(user);
		
	} 
	usersFile.close();
	return users;


}
