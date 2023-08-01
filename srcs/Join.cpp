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

const std::string Join::createChannel(Server &server, User &liveUser, std::vector<string> tokens) const{
	Channel *channel = new Channel(tokens[1], server.getUserPointer(liveUser.getFdSocket()));
	server.addChannel(tokens[1], channel);
	return ":" + liveUser.getNickname() + " " + tokens[0] + " " + tokens[1] + "\r\n";
}

// Faire fonctionner join avec plusieurs join channel d'affile + accepter keyword.
std::string Join::execute(Server &server,const string& message, User& liveUser) {
	string joinMessage;
	std::vector<string> tokens;

	tokens = tokenize(message, " ");
	if (tokens.size() == 1)
		return "461 PRIVMSG " + liveUser.getNickname() + " JOIN :Not enough parameters\r\n";
	else if (tokens[1][0] != '#') {
		joinMessage = "403 PRIVMSG " + tokens[1] + " :Channel name does not have '#' has prefix.\r\n";
	} else if (tokens[1].length() <= 1) {
		joinMessage = "403 PRIVMSG" + tokens[1] + " :Channel name is too short.\r\n";
	} else if (server.doesChannelExist(tokens[1])){
		Channel* channel = server.getChannel(tokens[1]);
		joinMessage = channel->addUser(&liveUser);
	}
	else
		joinMessage = createChannel(server, liveUser, tokens);
	tokens.clear();
	return (joinMessage);
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */