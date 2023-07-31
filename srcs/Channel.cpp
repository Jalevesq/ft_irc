#include "../include/Channel.hpp"
#include "../include/User.hpp"
#include <sys/socket.h>
#include <sstream>

/*
 *****************************************************************************
 **                              orthordox                                  **
 *****************************************************************************
*/
Channel::Channel(const std::string &name, User *user) : channelName_(name), topic_(""),
	userTopic_(""), password_(""), hasPassword_(false), mode_(0), userLimit_(0){
	users_[user] = true;
}

Channel::~Channel() {}

/*
 *****************************************************************************
 **                             broadcast                                   **
 *****************************************************************************
*/

//:irc.localhost 333 gurr #general dave!~dave@localhost 1690755553
void Channel::sendTopic(const User *user) const{
	std::string topic = ":ft_irc 332 " + user->getNickname() + " " + channelName_ + " :" + topic_ + "\r\n";
	send(user->getFdSocket(), topic.c_str(), topic.size(), 0);
	topic = ":ft_irc 333 " + user->getNickname() + " " + channelName_ + userTopic_ + " insert time here\r\n";
	send(user->getFdSocket(), topic.c_str(), topic.size(), 0);
}

//:irc.localhost 353 LOL = #general :LOL dave // FIX LATER WITH REAL STATUS instead of = ?
//:localhost 353 a = #a :a b
//:localhost 353 a = #c :dave dave1
//:localhost 315 LOL is :End of WHO list.
//:localhost 315 LOL is :End of WHO list.
void Channel::sendUserList(const User *user){
	std::map<User *, bool>::iterator it = users_.begin();
	std::ostringstream regularStream;
	std::string regularList;
	std::string endList;

	for (; it != users_.end(); ++it)
			regularStream << it->first->getNickname() << " ";
	regularList = ":localhost 353 " + user->getNickname() + " = " + channelName_ + " :" + regularStream.str() + "\r\n";
	send(user->getFdSocket(), regularList.c_str(), regularList.size(), 0);
	endList = ":localhost 315 " + user->getNickname() + " is :End of WHO list.\r\n";
	send(user->getFdSocket(), endList.c_str(), endList.size(), 0);
}

//:dave!~dave@localhost PART #general :gay
void Channel::sendUserLeft(const User *user, const std::string &reason){
	std::map<User *, bool>::iterator it = users_.begin();
	std::string message;
	for (; it != users_.end(); ++it){
		message = "PART " + channelName_ + " :" + reason + "\r\n";
		send(it->first->getFdSocket(), message.c_str(), message.size(), 0);
	}
	(void)user;
}

//:a!~a@localhost JOIN :#a
void Channel::sendUserJoin(const User *user, const std::string &reason){
	std::map<User *, bool>::iterator it = users_.begin();
	std::string message = ":" + user->getNickname() + "!~a@localhost JOIN :" + channelName_ + "\r\n";
	for (; it != users_.end(); ++it)
		send(it->first->getFdSocket(), message.c_str(), message.size(), 0);
	(void)reason;
}

/*
 *****************************************************************************
 **                            user methods                                 **
 *****************************************************************************
*/

//:dave!~user5@localhost JOIN :#general
const std::string Channel::addUser(User *user){
	std::map<User *, bool>::iterator it = users_.find(user);
	if (it != users_.end())
		return ""; //do nothing? unsure if the server I used is correct about that
	sendUserJoin(user, "bozo.com");
	users_[user] = false;
	if (!topic_.empty())
		sendTopic(user);;
	std::string tmp = ":" + user->getNickname() + " JOIN " + ":" + channelName_ + "\r\n";
	send(user->getFdSocket(), tmp.c_str(), tmp.size(), 0);
	sendUserList(user);
	return "";
}

//:gu!~a@localhost PART #B :
const std::string Channel::removeUser(User *user, const std::string &reason){
	users_.erase(user);
	sendUserLeft(user, reason);
	return "PART " + channelName_ + " :" + reason + "\r\n"; // double check
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
	return "BOZO";
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

bool Channel::hasPassword() const { return hasPassword_; }

int Channel::getMode() const { return mode_; }

int Channel::getUserLimit() const { return userLimit_; }