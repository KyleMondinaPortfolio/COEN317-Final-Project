#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "NodeList.h"


using namespace std;

NodeList::NodeList(char const *file_name){
	ifstream users_file(file_name);
	if(users_file){
		cout << "Successfully Open Users File " << endl; 
	}else{
		cout << "Unable to Open Users File" << endl;
	}
	string line;
	while(getline(users_file,line)){
		istringstream file_line(line);
		string guid, addr, p; 
		file_line >> guid;
		file_line >> addr;
		file_line >> p;
		Client user(stoi(guid), addr.c_str(), stoi(p));
		if ((add(user))<0){
			cout << "failed to add user: " << guid << " to the Node List" << endl;
		}else{
			cout << "added user: " << guid << " to the Node List"  << endl;
		}
		
	}
	users_file.close();
}
int NodeList::add(Client user){
	nodes.insert({user.name(),user});	
	return 1;
}

void NodeList::send_to_all(const Message &msg) const{
	for (auto itr = nodes.begin(); itr != nodes.end(); ++itr){
		itr->second.send_msg(msg);
	} 
}

void NodeList::send_to_all(const std::string &msg) const{
	for (auto itr = nodes.begin(); itr != nodes.end(); ++itr){
		itr->second.send_text(msg);
	} 
}
void NodeList::send_to(int guid, const Message &msg) const{
		const Client &client = nodes.at(guid);
		client.send_msg(msg);
}

void NodeList::show(){
	cout << "Users: " << endl;
	for (auto itr = nodes.begin(); itr != nodes.end(); ++itr){
		cout << itr->first << endl;
	} 
	
}

