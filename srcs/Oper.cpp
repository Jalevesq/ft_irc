#include "../include/Oper.hpp"
#include "../include/Utility.hpp"
#include "../include/Server.hpp"
#include "../include/User.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Oper::Oper()
{
}

// Oper::Oper( const Oper & src )
// {
// }


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Oper::~Oper()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

// Oper &				Oper::operator=( Oper const & rhs )
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

//RPL_YOUREOPER (381)  
// "<client> :You are now an IRC operator"
// Sent to a client which has just successfully issued an OPER command and gained operator status. The text used in the last param of this message varies wildly.


// /oper <user> <password>
string Oper::execute(Server &server,const string& message, User& liveUser) {
	std::vector<string> messageTokens;
	string userName, password;

	messageTokens = tokenize(message, " ");
	if (messageTokens.size() < 3) {
		return ("461 PRIVMSG " + liveUser.getNickname() + " OPER :Not enough parameters\r\n");
	} else if (messageTokens.size() > 3) {
		return ("400 :Error - Too many parameter in command oper.\r\n");
	}
	
	userName = messageTokens[1];
	password = messageTokens[2];

	if (password != OPER_PASSWORD) {
		return ("464 PRIVMSG: Bad Password you retard\r\n");
	}

	User *userToOper = server.doesUserExist(userName);
	if (userToOper == NULL) {
		return ("401 PRIVMSG :No such nickname.\r\n");
	}
	userToOper->setOperator(true);
	string operMessage = ": 381 " + userToOper->getNickname() + " :You are now an IRC operator\r\n";
	return (operMessage);
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */