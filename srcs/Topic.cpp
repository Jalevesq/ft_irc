#include "../include/Topic.hpp"
#include "../include/Server.hpp"
#include "../include/Utility.hpp"
#include "../include/User.hpp"

Topic::Topic(){}

Topic::~Topic(){}

//:gurr!~gurr@3263-666e-c7c8-29e5-42c9.67.68.ip TOPIC #42 :DUMBASS
//:irc.localhost 461 dave TOPIC :Not enough parameters

// Error Parsing.
// Check if channel exist, if is in channel and check if operator.
// Check topic length
// TOPIC #abc :fuck
std::string Topic::execute(Server &server, const string &message, User &liveUser){
	std::string sendTopicMessage;
	std::string topic;
	std::vector<std::string> token = tokenize(message, " ");

	if (token.size() < 3)
		return ("461 " + liveUser.getNickname() + " TOPIC :Not enough parameters\r\n");
	std::string channelName = token[1];
	if (!server.doesChannelExist(channelName))
		return ("403 " + channelName + " :No such channel\r\n");
	Channel * channel = server.getChannel(token[1]);
	if (!channel->isUserInChannel(liveUser.getNickname())) {
		return ("442 " + channelName + " :You're not on that channel\r\n");
	}

	size_t position = 1 + message.find(":");
	if (position == string::npos)
		return ("461 PRIVMSG :Bad format of command. Need ':' before message to send.\r\n");
	topic = message.substr(position);
	if (topic.length() > 35)
		return ("417 PRIVMSG :topic is too long.\r\n");

	channel->setTopic(topic, liveUser.getNickname());
	std::map<User *, bool> userList = channel->getUserList();
	std::map<User *, bool>::iterator it = userList.begin();
	sendTopicMessage = ":" + liveUser.getNickname() + " 332 " + liveUser.getNickname() + " " + channel->getChannelName() + " :" + topic + "\r\n";
	for (; it != userList.end(); it++) {
		send(it->first->getFdSocket(), sendTopicMessage.c_str(), sendTopicMessage.size(), 0);
	}		
	return "";
}