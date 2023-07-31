#include "../include/Privmsg.hpp"
#include "../include/Channel.hpp"
#include "../include/Server.hpp"

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

std::string Privmsg::execute(Server &server,const string& message, User& liveUser) {
	(void)server;
	(void)message;
	(void)liveUser;
	std::string destination, theMessage, privMessage;

	size_t start = message.find(' ');
    size_t end = message.find(':', start);

    if (start == std::string::npos || end == std::string::npos) {
        // Handle error
        return ("");
    }
    destination = message.substr(start + 1, (end - start) - 2);
    theMessage = message.substr(end + 1);

	theMessage += "\r\n";
	if (destination[0] == '#') {
		Channel *desti = server.getChannel(destination);
		desti->sendMessage(&liveUser, theMessage);
	}
	return ("");
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */