#pragma once

#include <iostream>
#include "Command.hpp"

using std::string;
using std::cout;
using std::endl;
using std::cerr;

class Mode : public Command {
public:
	Mode();
	~Mode();

	virtual string execute(Server &server,const string& message, User& liveUser);
private:
};