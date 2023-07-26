#include "../include/Command.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Command::Command()
{
	this->_commandList[NICK] = &Command::nickCommand;
	this->_commandList[JOIN] = &Command::joinCommand;
	this->_commandList[USER] = &Command::userCommand;
	this->_commandList[PING] = &Command::pingCommand;
}

// Command::Command( const Command & src )
// {
// }


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Command::~Command()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

// Command &				Command::operator=( Command const & rhs )
// {
// 	//if ( this != &rhs )
// 	//{
// 		//this->_value = rhs.getValue();
// 	//}
// 	return *this;
// }


/*
** -------------------------------- COMMANDS ----------------------------------
*/

const string Command::nickCommand(const string& message, const User& liveUser) {
	std::string nickMessage;
	
	nickMessage = ":" + liveUser.getNickname() + " NICK " + ":" + message.substr(5) + "\r\n";
	return (nickMessage);
}

const string Command::joinCommand(const string& message, const User& liveUser) { // need to set permision and all that, far from done at all
	std::string join;

	join = ":" + liveUser.getNickname() + " " + message + "\r\n";
	return (join);
}

const string Command::userCommand(const string& message, const User& liveUser) { // might need refacto so it works with the default name weechat give us
	string welcomeMessage;
	(void)liveUser;
	(void)message;
	
	welcomeMessage = "001 user :Welcome on ft_irc !\r\n";
	return (welcomeMessage);
}

const string Command::pingCommand(const string& message, const User& liveUser) {
	string pingMessage;
	(void)liveUser;

	pingMessage = "PONG " + message.substr(5) + "\r\n"; // think it works?
	return (pingMessage);
}

/*
** --------------------------------- METHODS ----------------------------------
*/

const string Command::parseCommand(const string& message, const string& command, const User& liveUser) {
	string finalMessage = "";
	MemberFunction functionCommand;
	
	functionCommand = _commandList[command];
	finalMessage = (this->*functionCommand)(message, liveUser);
	return (finalMessage);
}

const string Command::isCommand(const std::string &message) const {
	// Need more checkup for each command.
	if (message.empty())
		return ("");
	else if (message.find(NICK) == 0) {
		return (NICK);
	} else if (message.find(PING) == 0) {
		return (PING);
	} else if (message.find(USER) == 0) {
		return (USER);
	} else if (message.find(JOIN) == 0) {
		return (JOIN);
	} else {
		return ("");
	}
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */