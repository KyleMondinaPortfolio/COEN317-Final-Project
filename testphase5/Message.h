#ifndef MESSAGE_H
#define MESSAGE_H
#include <iostream>
#include <string>

class Message{
	public:
		Message(int sg, int tg, const std::string &t, const std::string &m):
			sguid(sg), tguid(tg), type(t), msg(m) {}
		int sguid;
		int tguid;
		std::string type;
		std::string msg;
		
};

#endif
