#ifndef USER_H
#define USER_H
#include <string>
#include <iostream>

class User {
	public:
		User(const std::string &n, const std::string &a, int p):
			name(n), addr(a), port(p) {}
		void display() const;
	private:
		std::string name;
		std::string addr;
		int port;
		
};
#endif
