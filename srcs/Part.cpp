#include "../include/Part.hpp"
#include "../include/Channel.hpp"
#include "../include/Server.hpp"
#include "../include/User.hpp"
#include "../include/Utility.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Part::Part()
{
	this->commandName_ = PART;
}

// Part::Part( const Part & src )
// {
// }


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Part::~Part()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

// Part &				Part::operator=( Part const & rhs )
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

string Part::execute(Server &server,const string& message, User& liveUser) {
	string channelName = "", info = "", partMessage = "";
	std::vector<string> messageTokens = tokenize(message, " ");

	if (messageTokens.size() <= 1) {
		return ("461 PRIVMSG " + liveUser.getNickname() + " PART :Not enough parameters.\r\n");
	} else if (!server.doesChannelExist(messageTokens[1])) {
		return ("403 PRIVMSG :No such channel\r\n");
	} 

	size_t pos = message.find(":", 0);
	if (pos == string::npos && messageTokens.size() > 2)
		return ("461 PRIVMSG :Bad format of command. Need ':' before reason to exit.\r\n");
	else if (pos == string::npos)
		info = "";
	else
		info = message.substr(pos + 1);

	if (info.length() > 25)
		return ("400 :Error - Part reason si too long.\r\n");
	Channel *channelToLeave = server.getChannel(messageTokens[1]);
	channelName = channelToLeave->getChannelName();
	if (!channelToLeave->isUserInChannel(liveUser.getNickname())) {
		return ("442 PRIVMSG " + channelName + " :You're not on that channel\r\n");
	} else {
		partMessage = channelToLeave->removeUser(&liveUser, info);
		liveUser.removeChannelUser(channelName);
		if (channelToLeave->getUserCount() == 0)
			server.removeChannel(channelName);
	}

	return (partMessage);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */