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

	//plus
	void parseModePlus(std::vector<string>::iterator &it, std::vector<string>::iterator &end, User &liveUser, Channel *channel, int &index, string &token);
	void setNoArgument(User &user, Channel *channel, const unsigned char &flag);
	void parseKeyMode(std::vector<string>::iterator &it, std::vector<string>::iterator &end, User &liveUser, Channel *channel);
	void parseModeOp(std::vector<string>::iterator &it, std::vector<string>::iterator &end, User &liveUser, Channel *channel);
	void parseModeLimit(std::vector<string>::iterator &it, std::vector<string>::iterator &end, User &liveUser, Channel *channel);

	//negative
	void parseModeNegatif(std::vector<string>::iterator &it, std::vector<string>::iterator &end, User &liveUser, Channel *channel, int &index, string &token);
	void setNoArgumentNegative(User &user, Channel *channel, const unsigned char &flag);
	void parseNegativeOP(std::vector<string>::iterator &it, std::vector<string>::iterator &end, User &liveUser, Channel *channel);

	//utility
	const string parseMode(Channel *channel, std::vector<string> &tokens, User &liveUser);
	void sendInvalidToken(string channelName, User &liveUser, const char c);
	void sendUserError(const string &message, int fd);
	virtual string execute(Server &server, const string& message, User& liveUser);
};