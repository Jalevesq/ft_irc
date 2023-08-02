#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <ctime>

class User;

#define MODE_INVITE_ONLY        0x01 // Bit 0 represents mode (i) invite only mode.
#define MODE_TOPIC_RESTRICTED   0x02 // Bit 1 represents mode (t) if the topic can only be changed by operator.
#define MODE_CHANNEL_KEY        0x04 // Bit 2 represents mode (k) if the channel is password protected.
#define MODE_CHANNEL_OPERATOR   0x08 // Bit 3 represents mode (o) ????
#define MODE_USER_LIMIT         0x10 // Bit 4 represents mode (i) if user limit is on

class Channel{
public:
	Channel(const std::string &name, User* user);
	//Channel(const Channel &rhs);
	~Channel();

	//Channel &operator=(const Channel &rhs);

	//user methods
	const std::string addUser(User* user);
	const std::string removeUser(User *user, const std::string &reason);

	//broadcast
	void sendNameChange(const User *user, const std::string &message);
	void sendTopic(const User *user) const;
	void sendUserList(const User *user);
	void sendUserLeft(const User *user, const std::string &reason);
	void sendUserJoin(const User *user);
	void sendMessage(const User *user, const std::string &message);

	//setter
	const std::string setMode(const unsigned char &mode, User *user);
	void setTopic(const std::string &topic, const std::string &userName);

	//getter
	const std::string &getChannelName() const;
	const std::string &getTopic() const;
	const std::string &getPassword() const;
	const std::map<User *, bool> &getUserList() const;
	int getUserCount() const;
	bool isOperator(User *user);
	bool hasPassword() const;
	bool isUserInChannel(const std::string& name);
	int getMode() const;
	int getUserLimit() const;
	
private:
	Channel();
	const std::string channelName_;
	std::string topic_;
	std::string password_;
	std::string userSetTopic_;
	time_t time_;
	std::map<User *, bool> users_;
	bool hasPassword_;
	unsigned char mode_;
	int userLimit_;
};