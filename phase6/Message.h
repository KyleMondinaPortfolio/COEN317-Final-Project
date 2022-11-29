#ifndef MESSAGE_H
#define MESSAGE_H
#include <iostream>
#include <string>


class Message{
	public:
		Message(std::string t, int sg, int tg, std::string m):
			type(t), sguid(sg), tguid(tg), msg(m) {}
		std::string mtype() const {return type;}
		int msguid() const {return sguid;}
		int mtguid() const {return tguid;}
		std::string mmsg() const {return msg;}
	private:
		std::string type;
		int sguid;
		int tguid;
		std::string msg;
		
};

std::string format_msg(Message msg);
Message parse_msg(std::string msg_str);

#endif
