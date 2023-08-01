#include "../include/Topic.hpp"
#include "../include/Server.hpp"
#include "../include/Utility.hpp"

Topic::Topic(){}

Topic::~Topic(){}

//:gurr!~gurr@3263-666e-c7c8-29e5-42c9.67.68.ip TOPIC #42 :DUMBASS
//:irc.localhost 461 dave TOPIC :Not enough parameters
std::string Topic::execute(Server &server, const string &message, User &liveUser){
	std::vector<std::string> token = tokenize(message);
	if (token.size() == 1)
		return "461 " + liveUser.getNickname() + " TOPIC :Not enough parameters\r\n";
	std::string channelName = token[1];
	size_t position = 1 + message.find(":");
	Channel * channel = server.getChannel(token[1]);
	channel->setTopic(message.substr(position), liveUser.getNickname());
	(void)server;
	return "";
}