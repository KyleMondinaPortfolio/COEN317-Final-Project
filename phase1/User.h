#ifndef USER_H
#define USER_H
#include <string>
#include <iostream>

class User {
	public:
		User(const std::string &n, const std::string &a, const std::string &p):
			name(n), addr(a), port(p) {}
		void display() const;
		std::string getName() const { return name; }
		std::string getAddr() const { return addr; }
		std::string getPort() const { return port; }
	private:
		std::string name;
		std::string addr;
		std::string port;
		
};
#endif
