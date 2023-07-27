#pragma once
#include "Command.hpp"
#include <map>
#include <vector>
#include <iostream>

class CommandFactory{
public:
	CommandFactory();
	// add other garbage later
	~CommandFactory();

	Command *CreateCommand();
	std::string ParseCommand(const std::string &command);
	const string checkDelimiter(User& liveUser);
	void SplitCommand(const std::string &command);
	void popCommand();
	const std::vector<std::string> &getVector() const;

	std::vector<std::string>::iterator getIteratorCmd(); 
	std::vector<std::string>::iterator getItEndteratorCmd();

private:
	std::map<std::string, Command *> map_;
	std::vector<std::string> cmd_;
};