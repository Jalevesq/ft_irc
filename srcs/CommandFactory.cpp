#include "../include/CommandFactory.hpp"
#include "../include/Nickname.hpp"
#include "../include/Join.hpp"
#include "../include/Username.hpp"
#include "../include/Ping.hpp"
#include "../include/Part.hpp"
#include "../include/Privmsg.hpp"
#include "../include/Topic.hpp"
#include "../include/Kick.hpp"
#include "../include/Mode.hpp"
#include "../include/Oper.hpp"
#include "../include/Invite.hpp"

CommandFactory::CommandFactory(){
	this->map_[PART] = new Part;
	this->map_[NICK] = new Nickname;
	this->map_[JOIN] = new Join; 
	this->map_[USER] = new Username;
	this->map_[PING] = new Ping;
	this->map_[PASSW] = new Pass;
	this->map_[PRIV] = new Privmsg;
	this->map_[TOPIC] = new Topic;
	this->map_[KICK] = new Kick;
	this->map_[MODE] = new Mode;
	this->map_[OPER] = new Oper;
	this->map_[INVITE] = new Invite;
}

CommandFactory::~CommandFactory(){
	for (std::map<std::string, Command *>::iterator it = map_.begin(); it != map_.end(); ++it)
		delete it->second;
}

Command *CommandFactory::CreateCommand(){
	std::string cmd = ParseCommand(*cmd_.begin());
	if (map_.find(cmd) != map_.end())
		return map_[cmd];
	else
		return NULL;
}

std::string CommandFactory::ParseCommand(const std::string &command){
	if (command.empty())
		return command;
	size_t position = command.find_first_of(" ");
	if (position == std::string::npos)
		return (command);
	else
		return command.substr(0, position);
}

void CommandFactory::SplitCommand(const std::string &command){
	size_t endPosition = 0;
	size_t startPosition = 0;
	for (size_t index = 0; index < command.size(); index++){
		if (command[index] == '\r' && command[index + 1] == '\n'){
			endPosition = index;
			cmd_.push_back(command.substr(startPosition, endPosition - startPosition));
			startPosition = endPosition + 2;
		}
	}
}

const string CommandFactory::checkDelimiter(User& liveUser) {
    string userMessage = liveUser.getMessage();
    string extractedMessage = "", newUserMessage = "";
    std::size_t found = userMessage.rfind("\n");
    if (found != std::string::npos) {
        extractedMessage = userMessage.substr(0, found + 1);
        newUserMessage = userMessage.substr(found + 1);
        liveUser.clearMessage();
        liveUser.appendMessage(newUserMessage);
        return (extractedMessage);
    }
    return ("");
}


std::vector<std::string>::iterator CommandFactory::getIteratorCmd() { return cmd_.begin(); }

std::vector<std::string>::iterator CommandFactory::getItEndteratorCmd() { return cmd_.end(); }

void CommandFactory::popCommand() { cmd_.erase(cmd_.begin()); }

const std::vector<std::string> &CommandFactory::getCmd() const { return cmd_; }