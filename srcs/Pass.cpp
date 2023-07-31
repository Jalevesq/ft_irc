#include "../include/Pass.hpp"
#include "../include/Server.hpp"

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

string Pass::execute(Server &server, const string& message, User& liveUser) {
	string entryPassword, finalMessage;
	(void)liveUser;
	const string& serverPassword = server.getPassword();

	entryPassword = message.substr(5);
	cout << "compare entry with real: '" << entryPassword << "' and '" << serverPassword << "'"<< endl;
	if (entryPassword.empty())
		finalMessage = "461 PRIVMSG :Need more parameter\r\n";
	else if (entryPassword == serverPassword) {
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