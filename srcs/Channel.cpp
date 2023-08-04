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
	password_(""), userSetTopic_(""), time_(0), hasPassword_(false), mode_(0), userLimit_(0){
	users_[user] = true;
	user->addChannelUser(channelName_);
}

Channel::~Channel() {
	std::vector<User *>::iterator it = this->inviteList_.begin();
	for (; it != inviteList_.end(); it++) {
		(*it)->removeChannelInInviteList(this);
	}
	inviteList_.clear();
}

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
    	topic =  ": 332 " + user->getNickname() + " " + channelName_ + " :" + topic_ + "\r\n";
		send(userSocket, topic.c_str(), topic.size(), 0);
		topic = ":" + this->userSetTopic_ + " 333 " + this->userSetTopic_  + " " + channelName_ + " " + this->userSetTopic_ + " " + std::to_string(time_) + "\r\n";
		send(userSocket, topic.c_str(), topic.size(), 0);
	}
}

void Channel::sendUserList(const User *user){
	std::map<User *, bool>::iterator it = users_.begin();
	std::ostringstream regularStream;
	std::string regularList;
	std::string endList;

	for (; it != users_.end(); ++it){
		if (it->first->getOperator())
			regularStream << "+";
		else if (it->second)
			regularStream << "@";
		regularStream << it->first->getNickname() << " ";
	}
	regularList = ":localhost 353 " + user->getNickname() + " = " + channelName_ + " :" + regularStream.str() + "\r\n";
	send(user->getFdSocket(), regularList.c_str(), regularList.size(), 0);
	endList = ":localhost 366 " + user->getNickname() + " " + channelName_ + " :End of /NAMES list\r\n";
	send(user->getFdSocket(), endList.c_str(), endList.size(), 0);
}

void Channel::sendUserLeft(const User *user, const std::string &reason){
	std::map<User *, bool>::iterator it = users_.begin();
	std::string message = ":" + user->getNickname() + " PART " + channelName_ + " :" + reason + "\r\n";
	for (; it != users_.end(); ++it)
		send(it->first->getFdSocket(), message.c_str(), message.size(), 0);
}

void Channel::broadCastUserList(){
	std::map<User *, bool>::iterator it = users_.begin();
	std::ostringstream regularStream;
	std::string regularList;

	for (; it != users_.end(); ++it){
		if (it->first->getOperator())
			regularStream << "+";
		else if (it->second)
			regularStream << "@";
		regularStream << it->first->getNickname() << " ";
	}
	regularList = "353 = " + channelName_ + " :" + regularStream.str() + "\r\n";
	for (it = users_.begin(); it != users_.end(); ++it)
		send(it->first->getFdSocket(), regularList.c_str(), regularList.size(), 0);
}

void Channel::sendUserJoin(const User *user) {
	std::map<User *, bool>::iterator it = users_.begin();
	std::string message = ":" + user->getNickname() + " JOIN :" + channelName_ + "\r\n";
	for (; it != users_.end(); ++it)
		send(it->first->getFdSocket(), message.c_str(), message.size(), 0);
}

void Channel::sendMessage(const User *user, const std::string &message){
	std::string messageToSend = ":" + user->getNickname() + " PRIVMSG " + channelName_ + " :" + message;
	std::map<User *, bool>::iterator it = users_.begin();
	for (; it != users_.end(); ++it){
		if (it->first->getFdSocket() != user->getFdSocket())
			send(it->first->getFdSocket(), messageToSend.c_str(), messageToSend.size(), 0);
	}
}

void Channel::sendCurrentMode(const User *user) const{
	std::ostringstream stream;
	std::string mode;
	if ((mode_ & 0b00011111) == 0)
		mode =  "324 " + user->getNickname() + " " + channelName_ + "\r\n";
	else{
		stream << " +";
		if (mode_ & MODE_USER_LIMIT)
			stream << "l";
		if (mode_ & MODE_CHANNEL_OPERATOR)
			stream << "o";
		if (mode_ & MODE_CHANNEL_KEY)
			stream << "k";
		if (mode_ & MODE_TOPIC_RESTRICTED)
			stream << "t";
		if (mode_ & MODE_INVITE_ONLY)
			stream << "i";
		std::string mode = "324 " + user->getNickname() + " " + channelName_ + stream.str() + "\r\n";
	}
	send(user->getFdSocket(), mode.c_str(), mode.size(), 0);
}

void Channel::broadCastAll(const std::string &message){
	std::map<User *, bool>::iterator it = users_.begin();
	for (; it != users_.end(); ++it)
		send(it->first->getFdSocket(), message.c_str(), message.size(), 0);
}

/*
 *****************************************************************************
 **                            user methods                                 **
 *****************************************************************************
*/

void Channel::addUser(User *user){
	std::map<User *, bool>::iterator it = users_.find(user);
	if (it != users_.end()) {
		string error = "443 PRIVMSG :You already are on this channel.\r\n";
		send(user->getFdSocket(), error.c_str(), error.size(), 0);
		return ;
	} else if (isUserInInviteList(user))
		removeUserInInviteList(user);
	sendUserJoin(user);
	user->addChannelUser(channelName_);
	if (user->getOperator())
		users_[user] = true;
	else
		users_[user] = false;
	std::string tmp = ":" + user->getNickname() + " JOIN " + ":" + channelName_ + "\r\n";
	send(user->getFdSocket(), tmp.c_str(), tmp.size(), 0);
	sendTopic(user);
	broadCastUserList();
}

const std::string Channel::removeUser(User *user, const std::string &reason){
	users_.erase(user);
	sendUserLeft(user, reason);
	return ":" + user->getNickname() + " PART " + channelName_ + " :" + reason + "\r\n";
}

std::string Channel::kickUser(User *userOp, User *toKick, const std::string &reason) {
	std::string message, partMessage = "";
	message = ":" + userOp->getNickname() + " KICK " + channelName_ + " " +  toKick->getNickname() + " :" + reason + "\r\n";
	std::map<User *, bool>::iterator it = users_.begin();
	for (; it != users_.end(); ++it){
		send(it->first->getFdSocket(), message.c_str(), message.size(), 0);
	}
	removeUser(toKick, "");
	return ("");
}


/*
 *****************************************************************************
 **                              setter                                     **
 *****************************************************************************
*/

//:aa!~a@localhost TOPIC #b :BUNCH OF BOZOS
void Channel::setTopic(const std::string &topic, const std::string &userName) {
	topic_ = topic;
	time_ = time(NULL);
	this->userSetTopic_  = userName;
}

void Channel::setPassword(const std::string &password){
	hasPassword_ = true;
	password_ = password;
}

void Channel::setUserOperator(User *user, bool flag) { users_[user] = flag; }

void Channel::setUserLimit(unsigned int amount) { userLimit_ = amount; }

/*
 *****************************************************************************
 **                               mode                                      **
 *****************************************************************************
*/

bool Channel::isModeFlagSet(const unsigned char &flag) const {
	return (mode_ & flag) == flag;
}

void Channel::setMode(const unsigned char &flag){ mode_ |= flag; }

void Channel::unsetMode(const unsigned char &flag){ mode_ &= ~flag; }

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

bool Channel::isUserInChannel(const std::string& name) {
	std::map<User *, bool>::iterator it = this->users_.begin();
	for (; it != users_.end(); it++) {
		if (name == it->first->getNickname())
			return (true);
	}
	return (false);
}

User *Channel::getUser(const std::string &name){
	std::map<User *, bool>::iterator it = this->users_.begin();
	for (; it != users_.end(); it++) {
		if (name == it->first->getNickname())
			return it->first;
	}
	return NULL;
}

bool Channel::isUserInInviteList(User *liveUser) {
	string liveUserNickname = liveUser->getNickname();
	std::vector<User *>::iterator it = inviteList_.begin();
	for (; it != inviteList_.end(); it++) {
		if ((*it)->getNickname() == liveUserNickname)
			return (true);
	}
	return (false);
}

void Channel::addUserInInviteList(User *liveUser) {
	this->inviteList_.push_back(liveUser);
}

void Channel::removeUserInInviteList(User *liveUser) {
	string liveUserNickname = liveUser->getNickname();
	std::vector<User *>::iterator it = inviteList_.begin();
	for (; it != inviteList_.end(); it++) {
		if ((*it)->getNickname() == liveUserNickname) {
			inviteList_.erase(it);
			break;
		}
	}
}

void Channel::clearUserInInviteList() {
	this->inviteList_.clear();
}

const std::string &Channel::getChannelName() const { return channelName_; }

const std::string &Channel::getTopic() const { return topic_; }

const std::string &Channel::getPassword() const { return password_; }

const std::map<User *, bool> &Channel::getUserList() const { return users_; }

int Channel::getUserCount() const { return users_.size(); }

bool Channel::hasPassword() const { return hasPassword_; }

int Channel::getMode() const { return mode_; }

int Channel::getUserLimit() const { return userLimit_; }