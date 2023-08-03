#include "../include/Topic.hpp"
#include "../include/Server.hpp"
#include "../include/Utility.hpp"
#include "../include/User.hpp"

Topic::Topic(){}

Topic::~Topic(){}

// Check if only operator mode is on in channel.
// TOPIC #abc :fuck
// TOPIC #abc
std::string Topic::execute(Server &server, const string &message, User &liveUser){
	std::string sendTopicMessage;
	std::string topic;
	std::vector<std::string> token = tokenize(message, " ");

	if (token.size() < 2)
		return ("461 " + liveUser.getNickname() + " TOPIC :Not enough parameters\r\n");
	std::string channelName = token[1];
	if (!server.doesChannelExist(channelName))
		return ("403 " + channelName + " :No such channel\r\n");
	Channel * channel = server.getChannel(token[1]);
	if (!channel->isUserInChannel(liveUser.getNickname())) {
		return ("442 " + channelName + " :You're not on that channel\r\n");
	}


	if (token.size() == 2) {
		channel->sendTopic(&liveUser);
		return ("");
	}
	size_t position = message.find(":");
	if (position == string::npos)
		return ("461 PRIVMSG :Bad format of command. Need ':' before topic to execute.\r\n");	
	if (token[2][0] == ':' && token[2].length() == 1) {
		topic = "";
	} else {
		topic = message.substr(position + 1);
		if (topic.length() > 35)
			return ("417 PRIVMSG :topic is too long.\r\n");
	}
	channel->setTopic(topic, liveUser.getNickname());

	std::map<User *, bool> userList = channel->getUserList();
	std::map<User *, bool>::iterator it = userList.begin();
	sendTopicMessage = ":" + liveUser.getNickname() + " 332 " + liveUser.getNickname() + " " + channel->getChannelName() + " :" + channel->getTopic() + "\r\n";
	for (; it != userList.end(); it++) {
		send(it->first->getFdSocket(), sendTopicMessage.c_str(), sendTopicMessage.size(), 0);
	}		

	return "";
}