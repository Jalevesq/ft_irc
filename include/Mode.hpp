#pragma once

#include <iostream>
#include "Command.hpp"
#include "Channel.hpp"
#include "User.hpp"

using std::string;
using std::cout;
using std::endl;
using std::cerr;

class Mode : public Command {
public:
	Mode();
	~Mode();

	virtual string execute(Server &server, const string& message, User& liveUser);
	const string parseMode(Channel *channel, std::vector<string> &tokens, User &liveUser);
	const string parseModePlus(std::vector<string>::iterator &it, std::vector<string>::iterator &end, User &liveUser, Channel *channel);
	const string parseModeNegatif(std::vector<string>::iterator &it, std::vector<string>::iterator &end, User &liveUser, Channel *channel);

	void sendInvalidToken(string channelName, User &liveUser, const char c);
};