#pragma once

#include <set>
#include <vector>
#include <iostream>

class User;

class Channel{
public:
	Channel(const std::string &name, const User* user);
	//Channel(const Channel &rhs);
	~Channel();

	//Channel &operator=(const Channel &rhs);
	
private:
	Channel();
	std::string channelName_;
	std::string topic_;
	std::string password_;
	std::set<User *> users_;
	std::set<User *> operators_;
	bool hasPassword_;
	int mode_;
	int userLimit_;
};