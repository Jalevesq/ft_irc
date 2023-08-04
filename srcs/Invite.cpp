#include "../include/Invite.hpp"
#include "../include/Utility.hpp"
#include "../include/User.hpp"
#include "../include/Server.hpp"
#include "../include/Channel.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Invite::Invite()
{
}

// Invite::Invite( const Invite & src )
// {
// }


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Invite::~Invite()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

// Invite &				Invite::operator=( Invite const & rhs )
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

// INVITE user #abc
// Si mode only invite is ON, check que le liveUser est un operateur
// send l'invite directement sur le FD du nickname ciblé (Checker si nickname existe)
// Check to can't invite yourself
string Invite::execute(Server &server,const string& message, User& liveUser) {
	string userNickname, channelName;
	std::vector<string> tokensMessage = tokenize(message, " ");
	if (tokensMessage.size() < 3) {
		return ("461 PRIVMSG :Not enough parameter in command invite\r\n");
	} else if (tokensMessage.size() > 3) {
		return("400 :Too many parameter in command invite\r\n");
	}
	userNickname = tokensMessage[1];
	channelName = tokensMessage[2];
	User *userToInvite;

	userToInvite = server.doesUserExist(userNickname);
	if (userToInvite == NULL) {
		return ("401 PRIVMSG :No such nickname '" + userNickname + "'\r\n");
	} else if (!server.doesChannelExist(channelName)) {
		return ("401 PRIVMSG :No such channel '" + channelName + "'\r\n");
	}
	Channel *channelInvite = server.getChannel(channelName);
	if (!channelInvite->isUserInChannel(liveUser.getNickname())) {
		return ("442 " + channelName + " :You're not on that channel.\r\n");
	} else if (channelInvite->isUserInChannel(userNickname)) {
		return ("443 " + userNickname + " " + channelName + " :is already on channel.\r\n");
	}
	
	bool isUserOp = channelInvite->isOperator(&liveUser);
	if (channelInvite->isModeFlagSet(MODE_INVITE_ONLY)) {
		if (!isUserOp)
			return ("482 " + channelName + " :You're not channel operator\r\n");
	}
	if (channelInvite->isUserInInviteList(userToInvite))
		return ("400 :" + userNickname + " is already invite in this channel\r\n");

	channelInvite->addUserInInviteList(userToInvite);
	userToInvite->addChannelInInviteList(channelInvite);
 	string inviteMessage = ":" + liveUser.getNickname() + " INVITE " + userNickname + " " + channelName + "\r\n";
    send(userToInvite->getFdSocket(), inviteMessage.c_str(), inviteMessage.size(), 0);
    return (": 341 " + liveUser.getNickname() + " " + userNickname + " " + channelName + "\r\n");
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */