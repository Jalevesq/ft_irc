#include "../include/CommandFactory.hpp"
#include "../include/Nickname.hpp"
#include "../include/Join.hpp"
#include "../include/Username.hpp"
#include "../include/Ping.hpp"

CommandFactory::CommandFactory(){ // refacto later
	this->map_[NICK] = new Nickname;
	this->map_[JOIN] = new Join;
	this->map_[USER] = new Username;
	this->map_[PING] = new Ping;
}

CommandFactory::~CommandFactory(){
	for (std::map<std::string, Command *>::iterator it = map_.begin(); it != map_.end(); ++it)
		delete it->second;
}

Command *CommandFactory::CreateCommand(const std::string &command){
	std::string cmd = ParseCommand(command);
	if (map_.find(cmd) != map_.end())
		return map_[cmd];
	else
		return NULL; //temporaire
}

std::string CommandFactory::ParseCommand(const std::string &command){
	if (command.empty())
		return command;
	size_t position = command.find_first_of(" ");
	return command.substr(0, position);
}

const bool& CommandFactory::checkDelimiter(const string& userMessage) {
	std::size_t found = userMessage.find("\r");
	if (found != string::npos && found + 1 < userMessage.length() && userMessage[found + 1] == '\n') {
		return (true);
	}
	return (false);
}
// void CommandFactory::SplitCommand(const std::string &command){
// 	// size_t index = 0;
// 	// size_t position = 0;
// 	// do
// 	// {
// 	// 	position = command.find("\r\n");
// 	// 	if (position == std::string::npos)
// 	// 		cmd_.push_back(command);
// 	// } while (index != std::string::npos);
// }