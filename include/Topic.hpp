#pragma once

#include <iostream>
#include "Command.hpp"

class Topic{
public:
	Topic();
	~Topic();

	virtual std::string execute(Server &server,const string& message, User& liveUser);
private:
};