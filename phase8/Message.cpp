#include <string>
#include "Message.h"

Message parse_msg(std::string msg_str){

	int first = msg_str.find("-");
	int second = msg_str.find("-",first+1);
	int third = msg_str.find("-",second+1);

	std::string type = msg_str.substr(0,first);
	int sguid = std::stoi(msg_str.substr(first+1,second-first-1));
	int tguid = std::stoi(msg_str.substr(second+1,third-second-1));
	std::string message = msg_str.substr(third+1,msg_str.find("~")-third);
	return Message(type,sguid,tguid,message);
}

std::string format_msg(Message msg){
		std::string msg_str(msg.mtype() + "-" + std::to_string(msg.msguid()) + "-" + std::to_string(msg.mtguid()) + "-" + msg.mmsg() + "~");
		return msg_str;
}

