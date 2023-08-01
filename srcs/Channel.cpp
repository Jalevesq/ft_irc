#include "../include/Channel.hpp"
#include "../include/User.hpp"
#include <sys/socket.h>
#include <sstream>
#include <string>

/*
 *****************************************************************************
 **                              orthordox                                  **
 *****************************************************************************
*/
Channel::Channel(const std::string &name, User *user) : channelName_(name), topic_(""),
	userTopic_(""), password_(""), UserSetTopic_(""), time_(0), hasPassword_(false), mode_(0), userLimit_(0){
	users_[user] = true;
	user->addChannelUser(channelName_);
}

Channel::~Channel() {}

/*
 *****************************************************************************
 **                             broadcast                                   **
 *****************************************************************************
*/

void Channel::sendNameChange(const User *user, const std::string &oldNickname){
	std::string message = ":" + oldNickname + " NICK " + user->getNickname() + " :" + oldNickname + " has changed their nickname to " + user->getNickname() + "\r\n";
	std::map<User *, bool>::iterator it = users_.begin();
	for (; it != users_.end(); ++it){
		// if (it->first->getFdSocket() != user->getFdSocket())
		send(it->first->getFdSocket(), message.c_str(), message.size(), 0);
	}
}

void Channel::sendTopic(const User *user) const{
	std::string topic;
	int userSocket = user->getFdSocket();
	if (topic_.empty()) {
		topic = "331 " + channelName_ + " :" + channelName_ +"\r\n";
		send(userSocket, topic.c_str(), topic.size(), 0);
	} else {
    	topic = ":" + user->getNickname() + " 332 " + user->getNickname() + " " + channelName_ + " :" + topic_ + "\r\n";
		send(userSocket, topic.c_str(), topic.size(), 0);
		topic = ":" + user->getNickname() + " 333 " + user->getNickname() + " " + channelName_ + " " + user->getNickname() + " " + std::to_string(time_) + "\r\n";
		send(userSocket, topic.c_str(), topic.size(), 0);
	}
}

void Channel::sendUserList(const User *user){
	std::map<User *, bool>::iterator it = users_.begin();
	std::ostringstream regularStream;
	std::string regularList;
	std::string endList;

	for (; it != users_.end(); ++it){
		if (it->second)
			regularStream << "@";
		regularStream << it->first->getNickname() << " ";
	}
	regularList = ":localhost 353 " + user->getNickname() + " = " + channelName_ + " :" + regularStream.str() + "\r\n";
	send(user->getFdSocket(), regularList.c_str(), regularList.size(), 0);
	endList = ":localhost 366 " + user->getNickname() + " " + channelName_ + " :End of Name list\r\n";;
	send(user->getFdSocket(), endList.c_str(), endList.size(), 0);
}

void Channel::sendUserLeft(const User *user, const std::string &reason){
	std::map<User *, bool>::iterator it = users_.begin();
	std::string message = ":" + user->getNickname() + " PART " + channelName_ + " :" + reason + "\r\n";
	for (; it != users_.end(); ++it)
		send(it->first->getFdSocket(), message.c_str(), message.size(), 0);
}

void Channel::sendUserJoin(const User *user, const std::string &reason){
	std::map<User *, bool>::iterator it = users_.begin();
	std::string message = ":" + user->getNickname() + " JOIN :" + channelName_ + "\r\n";
	for (; it != users_.end(); ++it)
		send(it->first->getFdSocket(), message.c_str(), message.size(), 0);
	(void)reason;
}

void Channel::sendMessage(const User *user, const std::string &message){
	std::string messageToSend = ":" + user->getNickname() + " PRIVMSG " + channelName_ + " :" + message;
	std::map<User *, bool>::iterator it = users_.begin();
	for (; it != users_.end(); ++it){
		if (it->first->getFdSocket() != user->getFdSocket())
			send(it->first->getFdSocket(), messageToSend.c_str(), messageToSend.size(), 0);
	}
}

/*
 *****************************************************************************
 **                            user methods                                 **
 *****************************************************************************
*/

const std::string Channel::addUser(User *user){
	std::map<User *, bool>::iterator it = users_.find(user);
	if (it != users_.end())
		return ("443 PRIVMSG :You already are on this channel.\r\n"); //do nothing? unsure if the server I used is correct about that
	// ajouter raison de join?
	sendUserJoin(user, "bozo.com");
	user->addChannelUser(channelName_);
	users_[user] = false;
	std::string tmp = ":" + user->getNickname() + " JOIN " + ":" + channelName_ + "\r\n";
	send(user->getFdSocket(), tmp.c_str(), tmp.size(), 0);
	sendTopic(user);
	sendUserList(user);
	return "";
}

const std::string Channel::removeUser(User *user, const std::string &reason){
	users_.erase(user);
	sendUserLeft(user, reason);
	return ":" + user->getNickname() + " PART " + channelName_ + " :" + reason + "\r\n";
}

/*
 *****************************************************************************
 **                              setter                                     **
 *****************************************************************************
*/

const std::string Channel::setMode(const unsigned char &mode, User *user){
	if (users_[user] == false)
		return ":irc.localhost 482 " + user->getNickname() + " " + channelName_ + " :You're not channel operator" + "\r\n"; //fix later to get real hostname
	(void)mode;
	return "BOZO\r\n";
}

//:aa!~a@localhost TOPIC #b :BUNCH OF BOZOS
void Channel::setTopic(const std::string &topic, const std::string &userName) {
	topic_ = topic;
	time_ = time(NULL);
	UserSetTopic_ = userName;
}

/*
 *****************************************************************************
 **                              getter                                     **
 *****************************************************************************
*/

bool Channel::isOperator(User *user){
	std::map<User *, bool>::iterator it = users_.find(user);
	if (it != users_.end())
		return it->second;
	else
		return false;
}

const std::string &Channel::getChannelName() const { return channelName_; }

const std::string &Channel::getTopic() const { return topic_; }

const std::string &Channel::getPassword() const { return password_; }

const std::map<User *, bool> &Channel::getUserList() const { return users_; }

int Channel::getUserCount() const { return users_.size(); }

bool Channel::hasPassword() const { return hasPassword_; }

int Channel::getMode() const { return mode_; }

int Channel::getUserLimit() const { return userLimit_; }