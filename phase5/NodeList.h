#ifndef NODELIST_H
#define NODELIST_H
#include "Client.h"
#include "Message.h"
#include <iostream>
#include <iterator>
#include <string>
#include <map>

class NodeList{
	public:
		NodeList() {}
		NodeList(char const *file_name);
		void send_to_all(const Message &msg) const; 
		void send_to_all(const std::string &msg) const; 
		//void send_to(int guid, const Message &msg) const;
		void send_to(int guid, const Message &msg) const;
		//int send_to_node(int guid, const Message &msg);
		//int removeNode(int guid);
		int add(Client usr);
		void show();
	private:
		std::map<int,Client> nodes;	
};

#endif
