#include "../include/Pass.hpp"
#include "../include/Server.hpp"
#include "../include/Utility.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Pass::Pass()
{
	this->commandName_ = PASSW;
}

// Pass::Pass( const Pass & src )
// {
// }


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Pass::~Pass()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

// Pass &				Pass::operator=( Pass const & rhs )
// {
// 	//if ( this != &rhs )
// 	//{
// 		//this->_value = rhs.getValue();
// 	//}
// 	return *this;
// }

/*
** --------------------------------- METHODS ----------------------------------
*/

// PASS secretpasswordhere

string Pass::execute(Server &server, const string& message, User& liveUser) {
	string entryPassword, finalMessage;
	std::vector<string> tokensMessage;
	const string& serverPassword = server.getPassword();

	if (liveUser.getIsPass() == true)
		return ("463 PRIVMSG :You're already register.\r\n");

	tokensMessage = tokenize(message, " ");
	if (tokensMessage.size() <= 1)
		return ("461 PRIVMSG :Need more parameter\r\n");

	entryPassword = tokensMessage[1];
	if (entryPassword == serverPassword) {
		liveUser.setIsPass (true);
		finalMessage = "451 PRIVMSG :You are not registered. Please give a nickname (/nick <nickname>) and a Username (USER <user> 0 * :<real name>)\r\n";
	} else {
		finalMessage = "464 PRIVMSG :Wrong Password. If you're using a client, you might need to set the password in settings and reconnect.\r\n";
	}
	// Disconnect user quand bad passwd?
	return (finalMessage);
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */