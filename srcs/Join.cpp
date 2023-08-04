#include "../include/Join.hpp"
#include "../include/Utility.hpp"
#include "../include/Server.hpp"
#include "../include/User.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Join::Join()
{
	this->commandName_ = JOIN;
}

// Join::Join( const Join & src )
// {
// }


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Join::~Join()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

// Join &				Join::operator=( Join const & rhs )
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

void	Join::createChannel(Server &server, User &liveUser, std::map<string, string>::iterator it) const {
	if (server.getChannelCount() >= MAX_CHANNEL) {
		string error = "400 :Error - Max channel on server reach. Impossible to create new channel.\r\n";
		send(liveUser.getFdSocket(), error.c_str(), error.size(), 0);
		return ;
	}
	Channel *channel = new Channel(it->first, &liveUser);
	server.addChannel(it->first, channel);
	std::string tmp = ":" + liveUser.getNickname() + " JOIN " + it->first + "\r\n";
	send(liveUser.getFdSocket(), tmp.c_str(), tmp.size(), 0);
	channel->sendTopic(&liveUser);
	channel->sendUserList(&liveUser);
}

string errorChecker(std::vector<string> &tokens, std::vector<string> &channelToJoin, std::vector<string> &keyword, User& liveUser) {
	if (tokens.size() <= 1)
		return ("461 PRIVMSG " + liveUser.getNickname() + " JOIN :Not enough parameters\r\n");
	else if (tokens.size() > 3)
		return ("400 :Error - Too many parameter in command join.\r\n");
	
	if (tokens.size() >= 2)
		channelToJoin = tokenize(tokens[1], ",");
	if (tokens.size() >= 3)
		keyword = tokenize(tokens[2], ",");

	if (channelToJoin.size() > 2) {
		return ("400 :Error - Try to join too many channel at the same time. Nothing has been executed.\r\n");
	} else if (keyword.size() > channelToJoin.size()) {
		return ("400 :Error - You entered more keyword than channel. Nothing has been executed.\r\n");
	}
	return ("");
}

void 	fill_map_channel_n_key(std::map<string, string> &channelAndKey, std::vector<string> &channelToJoin, std::vector<string> &keyword) {
	string keyChannel = "";
	string joinChannel = "";

	for (unsigned int i = 0; i <= channelToJoin.size(); i++) {
		if (!keyword.empty()) {
			keyChannel = keyword.back();
			keyword.pop_back();
		} else
			keyChannel = "";
	
		joinChannel = channelToJoin.back();
		channelToJoin.pop_back();

		channelAndKey[joinChannel] = keyChannel;
	}
}

bool checkMode(Channel *channel, User *liveUser, string keyword) {
	string error = "";
	string channelName = channel->getChannelName();
	if (liveUser->getOperator())
		return (true);
	if (channel->isModeFlagSet(MODE_INVITE_ONLY)) {
		error = "471 PRIVMSG :Cannot join, invite only channel (+i)\r\n";
		if (!channel->isUserInInviteList(liveUser)) {
			send(liveUser->getFdSocket(), error.c_str(), error.size(), 0);
			return (false);
		}
	}
	if (channel->isModeFlagSet(MODE_CHANNEL_KEY)) {
  		error = "475 " + channelName + " :Cannot join, bad channel key (+k)\r\n";
		if (keyword != channel->getPassword()) {
			send(liveUser->getFdSocket(), error.c_str(), error.size(), 0);
			return (false);
		}
	}
	if (channel->isModeFlagSet(MODE_USER_LIMIT)) {
		error =  "471 " + channelName + " :Cannot join, limit user in channel reach (+l)\r\n";
		if (channel->getUserList().size() >= static_cast<unsigned long>(channel->getUserLimit())) {
			send(liveUser->getFdSocket(), error.c_str(), error.size(), 0);
			return (false);
		}
	}
	return (true);
}

string Join::loop_through_map(std::map<string, string> &channelAndKey,User& liveUser, Server &server) {
	string errorMessage;

	std::map<std::string, std::string>::iterator it = channelAndKey.begin();
	for (; it != channelAndKey.end(); it++) {
		errorMessage = "";
		if (liveUser.getChannelSet().size() >= MAX_CHANNEL_PER_USER) {
    		return ("400 :Error - You have reached your maximum channel limit: " + std::to_string(MAX_CHANNEL_PER_USER) + "\r\n");
		}
		if (it->first[0] != '#')
			errorMessage = "403 PRIVMSG '" + it->first + "' :Channel name does not have '#' has prefix.\r\n";
		else if (it->first.find(":", 0) != string::npos)
			errorMessage = "403 PRIVMSG '" + it->first + "' :Forbidden char ':' in channel name.\r\n";
		else if (it->first.length() > 10)
			errorMessage = "400 :Channel name is too long: " + it->first + "\r\n";
		else if (it->second.length() > 10)
			errorMessage = "400 :Error - Keyword for channel " + it->first + " is too long.\r\n";
		else if (it->second.find(" ", 0) != string::npos)
			errorMessage = "696 " + it->first + "k :Forbidden char in keyword\r\n";
		if (!errorMessage.empty()) {
			send(liveUser.getFdSocket(), errorMessage.c_str(), errorMessage.size(), 0);
			continue;
		}

		if (server.doesChannelExist(it->first)) {
			Channel *channel = server.getChannel(it->first);
			if (!checkMode(channel, &liveUser, it->second))
				continue;
			channel->addUser(&liveUser);
		} else {
			createChannel(server, liveUser, it);
		}
	}
	return ("");
}

std::string Join::execute(Server &server,const string& message, User& liveUser) {
	string errorMessage = "";

	std::vector<string> tokens;
	std::vector<string> channelToJoin;
	std::vector<string> keyword;
	std::map<string, string> channelAndKey;

	tokens = tokenize(message, " ");
	errorMessage = errorChecker(tokens, channelToJoin, keyword, liveUser);
	if (!errorMessage.empty()) {
		return (errorMessage);
	}

	fill_map_channel_n_key(channelAndKey, channelToJoin, keyword);
	errorMessage = loop_through_map(channelAndKey, liveUser, server);
	
	return (errorMessage);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */