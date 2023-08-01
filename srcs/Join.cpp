#include "../include/Join.hpp"
#include "../include/Utility.hpp"
#include "../include/Server.hpp"

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

// TO re-do with mode?
const std::string Join::createChannel(Server &server, User &liveUser, std::unordered_map<string, string>::iterator it) const{
	Channel *channel = new Channel(it->first, server.getUserPointer(liveUser.getFdSocket()));
	server.addChannel(it->first, channel);
	std::string tmp = ":" + liveUser.getNickname() + " JOIN " + it->first + "\r\n";
	send(liveUser.getFdSocket(), tmp.c_str(), tmp.size(), 0);
	channel->sendTopic(&liveUser);
	channel->sendUserList(&liveUser);
	return "";
}

// Faire fonctionner join avec plusieurs join channel d'affile + accepter keyword.
// limite par commande de 3 channels d'une shot
// TO DO ME: Refaire join, Topic puis Kick

// JOIN: Check la length de chaque chose passé en paramètre

// Check pour nickname et privmsg pour que le nbr d'argument quand tokenize soit pas trop *****

// Quand MODE fait ajouter: Impossible de join quand ban, invite only, limite utilisateur, etc.
std::string Join::execute(Server &server,const string& message, User& liveUser) {
	(void)server;
	(void)liveUser;

	string joinMessage, errorMessage;
	string joinChannel = "";
	string keyChannel = "";

	std::vector<string> tokens;
	std::vector<string> channelToJoin;
	std::vector<string> keyword;
	std::unordered_map<string, string> channelAndKey;

	tokens = tokenize(message, " ");
	if (tokens.size() <= 1)
		return "461 PRIVMSG " + liveUser.getNickname() + " JOIN :Not enough parameters\r\n";
	else if (tokens.size() > 3)
		;// error
	
	if (tokens.size() >= 2)
		channelToJoin = tokenize(tokens[1], ",");
	if (tokens.size() >= 3)
		keyword = tokenize(tokens[2], ",");

	for (unsigned int i = 0; i < channelToJoin.size(); i++) {
		if (!keyword.empty()) {
			keyChannel = keyword.front();
			keyword.erase(keyword.begin());
		} else
			keyChannel = "";
	
		joinChannel = channelToJoin.front();
		channelToJoin.erase(channelToJoin.begin());

		channelAndKey[joinChannel] = keyChannel;
	}

	if (!keyword.empty()) {
		joinMessage = "400 PRIVMSG :You entered more keyword than channel. Nothing has been executed.\r\n";
		return (joinMessage);
	}

	// needs more checkup for password. No space are accepted.
	std::unordered_map<string,string>::iterator it = channelAndKey.begin();
	for (; it != channelAndKey.end(); it++) {
		errorMessage = "";
		if (it->first[0] != '#')
			errorMessage = "403 PRIVMSG " + it->first + " :Channel name does not have '#' has prefix.\r\n";
		else if (it->first.length() > 10)
			errorMessage = "400 PRIVMSG :Channel name is too long: " + it->first + "\r\n";
		else if (it->second.length() > 10)
			errorMessage = "400 PRIVMSG :Keyword for channel " + it->first + " is too long.\r\n";
		else if (it->second.find(" ", 0) != string::npos)
			errorMessage = "696 " + it->first + "k :Forbidden char in keyword\r\n";
		if (!errorMessage.empty()) {
			send(liveUser.getFdSocket(), errorMessage.c_str(), errorMessage.size(), 0);
			continue;
		}
		else if (server.doesChannelExist(it->first)) {
			Channel *channel = server.getChannel(it->first);
			joinMessage = channel->addUser(&liveUser);
		} else {
			joinMessage = createChannel(server, liveUser, it);
		}
	}

	cout << "- Channel -" << endl;
	for (unsigned int i = 0; i < channelToJoin.size(); i++)
		cout << "'" << channelToJoin[i] << "'" << endl;
	cout << "- keyword -" << endl;
	for (unsigned int i = 0; i < keyword.size(); i++)
		cout << "'" << keyword[i] << "'" << endl;

	return (joinMessage);
}

	// else if (tokens[1][0] != '#') {
	// 	joinMessage = "403 PRIVMSG " + tokens[1] + " :Channel name does not have '#' has prefix.\r\n";
	// } else if (server.doesChannelExist(tokens[1])){
	// 	Channel* channel = server.getChannel(tokens[1]);
	// 	joinMessage = channel->addUser(&liveUser);
	// }
	// else
	// 	joinMessage = createChannel(server, liveUser, tokens);
	// tokens.clear();

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */