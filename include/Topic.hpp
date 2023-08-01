#pragma once

#include <iostream>
#include "Command.hpp"

using std::string;
using std::cout;
using std::endl;

class Topic : public Command{
public:
	Topic();
	~Topic();

	virtual std::string execute(Server &server,const string& message, User& liveUser);
private:
};