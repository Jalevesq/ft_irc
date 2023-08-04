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
		return ("464 PRIVMSG :Bad Password\r\n");
	}

	User *userToOper = server.doesUserExist(userName);
	if (userToOper == NULL) {
		return ("401 PRIVMSG :No such nickname.\r\n");
	}


	userToOper->setOperator(true);
	std::set<string> channelSetUser = userToOper->getChannelSet();
	std::set<string>::iterator it = channelSetUser.begin();
	for (; it != channelSetUser.end(); it++) {
		Channel* channel = server.getChannel(*it);
		channel->setUserOperator(userToOper, true);
		channel->broadCastUserList();
	}
	string operMessage = ": 381 " + userToOper->getNickname() + " :You are now an IRC operator\r\n";
	send(userToOper->getFdSocket(), operMessage.c_str(), operMessage.size(), 0);
	return ("");
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */