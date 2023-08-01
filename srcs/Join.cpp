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

void Join::tokenizeJoin(const string &message){
	std::string token;
	size_t index = 0;
	size_t end = message.find(" ");

	while (end != std::string::npos){
		token = message.substr(index, end - index);
		if (isNotEmptyString(token) && token.find(" ") == std::string::npos)
			tokens_.push_back(token);
		index = end + 1;
		end = message.find(" ", index);
	}
	token = message.substr(index);
	if (isNotEmptyString(token) && token.find(" ") == std::string::npos)
		tokens_.push_back(token);
}

const std::string Join::createChannel(Server &server, User &liveUser) const{
	Channel *channel = new Channel(tokens_[1], server.getUserPointer(liveUser.getFdSocket()));
	server.addChannel(tokens_[1], channel);
	return ":" + liveUser.getNickname() + " " + tokens_[0] + " " + tokens_[1] + "\r\n";
}

std::string Join::execute(Server &server,const string& message, User& liveUser) {
	string joinMessage;

	tokenizeJoin(message);
	if (tokens_.size() == 1)
		return "461 PRIVMSG" + liveUser.getNickname() + " JOIN :Not enough parameters\r\n";
	else if (tokens_[1][0] != '#') {
		joinMessage = "403 PRIVMSG " + tokens_[1] + " :Channel name does not have '#' has prefix.\r\n";
	} else if (tokens_[1].length() <= 1) {
		joinMessage = "403 PRIVMSG" + tokens_[1] + " :Channel name is too short.\r\n";
	} else if (server.doesChannelExist(tokens_[1])){
		Channel* channel = server.getChannel(tokens_[1]);
		joinMessage = channel->addUser(&liveUser);
	}
	else
		joinMessage = createChannel(server, liveUser);
	tokens_.clear();
	return (joinMessage);
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */