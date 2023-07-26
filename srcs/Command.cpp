#include "../include/Command.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Command::Command()
{

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

// const string Command::nickCommand(const string& message, User& liveUser) {
// 	string nickMessage;
// 	string newNickname;
	
// 	// Add protection to check if newNickname is valid
// 	newNickname = message.substr(5);
// 	nickMessage = ":" + liveUser.getNickname() + " NICK " + ":" + newNickname + "\r\n";
// 	cout << "newNickname: '" << newNickname << "'" << endl; 
// 	liveUser.setNickname(newNickname);
// 	return (nickMessage);
// }

// const string Command::joinCommand(const string& message, User& liveUser) { // need to set permision and all that, far from done at all
// 	string join;

// 	join = ":" + liveUser.getNickname() + " " + message + "\r\n";
// 	return (join);
// }

// const string Command::userCommand(const string& message, User& liveUser) { // might need refacto so it works with the default name weechat give us
// 	string welcomeMessage;
// 	(void)liveUser;
// 	(void)message;
	
// 	welcomeMessage = "001 user :Welcome on ft_irc !\r\n";
// 	return (welcomeMessage);
// }

// const string Command::pingCommand(const string& message, User& liveUser) {
// 	string pingMessage;
// 	(void)liveUser;

// 	pingMessage = "PONG " + message.substr(5) + "\r\n"; // think it works?
// 	return (pingMessage);
// }

/*
** --------------------------------- METHODS ----------------------------------
*/


/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */