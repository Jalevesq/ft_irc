#include "../include/Part.hpp"
#include "../include/Channel.hpp"
#include "../include/Server.hpp"

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
	(void)server;
	(void)message;
	(void)liveUser;
	string channelName, info, partMessage;

	size_t start = message.find('#');
    size_t end = message.find(':', start);

    if (start == std::string::npos || end == std::string::npos) {
        // Handle error
        return ("");
    }
    channelName = message.substr(start, end - (start + 1));
    info = message.substr(end + 1);

	Channel *channel = server.getChannel(channelName);
	partMessage = channel->removeUser(&liveUser, info);

	return (partMessage);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */