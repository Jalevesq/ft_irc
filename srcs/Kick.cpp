#include "../include/Kick.hpp"
#include "../include/Utility.hpp"
#include "../include/Server.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Kick::Kick()
{
}

// Kick::Kick( const Kick & src )
// {
// }


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Kick::~Kick()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

// Kick &				Kick::operator=( Kick const & rhs )
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

// KICK #Finnish Matthew   
// KICK #Finnish John :Speaking English

string Kick::execute(Server &server,const string& message, User& liveUser) {
	(void)server;
	(void)message;
	User *userToKick;
	Channel *channelFromKick;
	string kickMessage = "";
	string reason = "";
	std::vector<string> messageTokens;

	messageTokens = tokenize(message, " ");
	if (messageTokens.size() < 3) {
		return ("461 PRIVMSG " + liveUser.getNickname() + " KICK :Not enough parameters.\r\n");
	} else if (!server.doesChannelExist(messageTokens[1])) {
		return ("401 PRIVMSG :No such channel.\r\n");
	}
	channelFromKick = server.getChannel(messageTokens[1]);
	userToKick = server.doesUserExist(messageTokens[2]);
	if (userToKick == NULL)
		return ("401 PRIVMSG :No such nickname.\r\n");
	else if (!channelFromKick->isUserInChannel(liveUser.getNickname())) {
		return ("442 PRIVMSG :You're not on that channel.\r\n");
	} else if (!channelFromKick->isOperator(&liveUser)) {
		return ("482 PRIVMSG :You're not an operator on this channel.\r\n");
	} else if (!channelFromKick->isUserInChannel(userToKick->getNickname())) {
		return ("441 PRIVMSG :User " + userToKick->getNickname() + " is not on this channel.\r\n");
	} else if (userToKick->getNickname() == liveUser.getNickname()) {
		return ("400 :Error - You can't kick yourself dumbfuck.\r\n");
	}  else if (channelFromKick->isOperator(userToKick) && liveUser.getOperator() == false) {
		// userToKick is channel Op et userThatKick is not global op
		return ("723 Kick :Error - User " + userToKick->getNickname() + " is a Channel Operator.\r\n");
	} else if (userToKick->getOperator()) {
		return ("400 Kick :User " + userToKick->getNickname() + " is a Global Operator.\r\n");
	}

	if (messageTokens.size() >= 4) {
		size_t pos = message.find(":", 0);
		if (pos == string::npos)
			return ("461 PRIVMSG :Bad format of command. Need ':' before reason to kick.\r\n");
		else
			reason = message.substr(pos + 1);
	}
	if (reason.length() > 40) {
		return ("400 :Error - Kick reason is too long\r\n");
	}
	kickMessage = channelFromKick->kickUser(&liveUser, userToKick, reason);
	userToKick->removeChannelUser(channelFromKick->getChannelName());
	return (kickMessage);

}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */