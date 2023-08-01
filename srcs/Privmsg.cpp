#include "../include/Privmsg.hpp"
#include "../include/Channel.hpp"
#include "../include/Server.hpp"
#include "../include/Utility.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Privmsg::Privmsg()
{
}

// Privmsg::Privmsg( const Privmsg & src )
// {
// }


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Privmsg::~Privmsg()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

// Privmsg &				Privmsg::operator=( Privmsg const & rhs )
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

string Privmsg::channelMessage(User &liveUser, std::vector<string> &infoMessage, Server& server) {
	string privMessage = "";

	if (!server.doesChannelExist(infoMessage[DEST])) {
		privMessage = "403 PRIVMSG :No such channel\r\n";
	} else if (!isUserInChannel(liveUser, infoMessage[DEST])) {
		privMessage = "441 PRIVMSG :You are not on this channel\r\n";
	} else {
		Channel *desti = server.getChannel(infoMessage[DEST]);
		desti->sendMessage(&liveUser, infoMessage[MSG]);
	}
	return (privMessage);
}

string Privmsg::privateMessage(User &liveUser, std::vector<string> &infoMessage, Server& server) {
	string privMessage = "";

	User *userDestination = server.doesUserExist(infoMessage[DEST]);
	if (userDestination == NULL)
		privMessage = "401 PRIVMSG :No such nickname\r\n";
	else if (userDestination->getNickname() == liveUser.getNickname()) {
		privMessage = "400 PRIVMSG :You can't send a message to yourself\r\n";
	} else {
		string msgPrivate = ":" + liveUser.getNickname() + " PRIVMSG " + userDestination->getNickname() + " :" + infoMessage[MSG];
		send(userDestination->getFdSocket(), msgPrivate.c_str(), msgPrivate.size(), 0 );
	}
	return (privMessage);
}

bool Privmsg::isUserInChannel(User& liveUser, string &destination) {
	std::set<string> userChannelList = liveUser.getChannelSet();
	if (userChannelList.find(destination) != userChannelList.end())
		return (true);
	return (false);
}

std::string Privmsg::execute(Server &server,const string& message, User& liveUser) {
	std::string privMessage = "";
	std::vector<string> messageToken = tokenize(message);
	std::vector<string> infoMessage;

	if (messageToken.size() < 2) {
		privMessage = "411 PRIVMSG :No recipient\r\n";
		return (privMessage);
	} else if (messageToken.size() < 3 || messageToken[2].size() <= 1) {
		privMessage = "412 PRIVMSG :No text to send\r\n";
		return (privMessage);
	} else if (messageToken[2][0] != ':') {
		privMessage = "461 PRIVMSG :Bad format of command. Need ':' before message to send.\r\n";
		return (privMessage);
	}

	infoMessage.push_back(messageToken[1]);
	infoMessage.push_back("");
	// Changer le tokenizer pcq remove ' '. 
	for (unsigned int i = 2; i < messageToken.size(); i++)
		infoMessage[MSG] += messageToken[i] + " ";

	infoMessage[MSG].erase(0, 1);
	if (infoMessage[MSG].length() > 100) {
		privMessage = "417 PRIVMSG :message is too long\r\n";
		return (privMessage);
	}

	infoMessage[MSG] += "\r\n";
	if (infoMessage[DEST][0] == '#')
		privMessage = channelMessage(liveUser, infoMessage, server);
	else
		privMessage = privateMessage(liveUser, infoMessage, server);
	return (privMessage);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */