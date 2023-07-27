#include "Command.hpp"
#include <map>
#include <vector>
#include <iostream>

class CommandFactory{
public:
	CommandFactory();
	// add other garbage later
	~CommandFactory();

	Command *CreateCommand(const std::string &command);
	std::string ParseCommand(const std::string &command);
	void SplitCommand(const std::string &command);

private:
	std::map<std::string, Command *> map_;
	std::vector<std::string> cmd_;
};