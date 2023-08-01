#include "../include/Topic.hpp"
#include "../include/Server.hpp"
#include "../include/Utility.hpp"
#include "../include/User.hpp"

Topic::Topic(){}

Topic::~Topic(){}

//:irc.localhost 461 dave TOPIC :Not enough parameters

// Error Parsing + dispatch a tt le monde quand topic change
std::string Topic::execute(Server &server, const string &message, User &liveUser){
	std::string sendTopicMessage;
	std::string topic;
	std::vector<std::string> token = tokenize(message);

	if (token.size() == 1)
		return "461 " + liveUser.getNickname() + " TOPIC :Not enough parameters\r\n";
	std::string channelName = token[1];
	size_t position = 1 + message.find(":");
	// Check que le channel existe
	Channel * channel = server.getChannel(token[1]);

	topic = message.substr(position);
	channel->setTopic(topic);
	std::map<User *, bool> userList = channel->getUserList();
	std::map<User *, bool>::iterator it = userList.begin();

	sendTopicMessage = ":" + liveUser.getNickname() + " 332 " + liveUser.getNickname() + " " + channel->getChannelName() + " :" + topic + "\r\n";
	for (; it != userList.end(); it++) {
		send(it->first->getFdSocket(), sendTopicMessage.c_str(), sendTopicMessage.size(), 0);
	}		
	return "";
}