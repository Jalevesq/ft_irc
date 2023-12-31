#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <ctime>

class User;

/*
*/

#define MODE_INVITE_ONLY        0x01 // Bit 0 represents mode (i) invite only mode.
#define MODE_TOPIC_RESTRICTED   0x02 // Bit 1 represents mode (t) if the topic can only be changed by operator.
#define MODE_CHANNEL_KEY        0x04 // Bit 2 represents mode (k) if the channel is password protected.
#define MODE_CHANNEL_OPERATOR   0x08 // Bit 3 represents mode (o) give or remove operator to an user
#define MODE_USER_LIMIT         0x10 // Bit 4 represents mode (i) if user limit is on

class Channel{
public:
	Channel(const std::string &name, User* user);
	~Channel();

	//user methods
	void	addUser(User* user);
	const std::string removeUser(User *user, const std::string &reason);
	std::string kickUser(User *userOp, User *toKick, const std::string &reason);

	//broadcast
	void sendNameChange(const User *user, const std::string &message);
	void sendTopic(const User *user) const;
	void sendUserList(const User *user);
	void sendMessage(const User *user, const std::string &message);
	void sendCurrentMode(const User *user) const;
	void broadCastAll(const std::string &message);
	void broadCastUserList();

	//setter
	void setTopic(const std::string &topic, const std::string &userName);
	void setPassword(const std::string &password);
	void setUserOperator(User *user, bool flag);
	void setUserLimit(unsigned int amount);

	//getter
	const std::string &getChannelName() const;
	const std::string &getTopic() const;
	const std::string &getPassword() const;
	const std::map<User *, bool> &getUserList() const;
	int getUserCount() const;
	bool isOperator(User *user);
	bool isUserInChannel(const std::string& name);
	int getMode() const;
	int getUserLimit() const;
	User *getUser(const std::string &user);

	//mode
	bool isModeFlagSet(const unsigned char &flag) const;
	void setMode(const unsigned char &flag);
	void unsetMode(const unsigned char &flag);

	// userList
	bool isUserInInviteList(User *liveUser);
	void addUserInInviteList(User *liveUser);
	void removeUserInInviteList(User *liveUser);
	void clearUserInInviteList();
	
private:
	Channel();
	const std::string channelName_;
	std::string topic_;
	std::string password_;
	std::string userSetTopic_;
	time_t time_;
	std::vector<User *> inviteList_;
	std::map<User *, bool> users_;
	unsigned char mode_;
	int userLimit_;
};