#include "../include/Topic.hpp"
#include "../include/Server.hpp"
#include "../include/Utility.hpp"

Topic::Topic(){}

Topic::~Topic(){}

//TOPIC #hub :a
std::string Topic::execute(Server &server, const string &message, User &liveUser){
	std::vector<std::string> token_ = tokenize(message);
	if (token_.size() == 1)
		return "461 PRIVMSG" + liveUser.getNickname() + " TOPIC :Not enough parameters\r\n";
	cout << token_[1] << endl;
	(void)server;
	(void)liveUser;
	return "BOZO";
}