#ifndef USERS_H
#define USERS_H
#include <vector>
#include <vector>
#include "User.h"

class Users{
	public:
		void addUser(User *user) { users.push_back(user); }
		void displayUsers();
		void displayUserNames();
	private:
		std::vector<User*> users;
}; 


#endif
