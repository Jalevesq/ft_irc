#include "../include/Username.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Username::Username()
{
	this->commandName_ = USER;
}

// Username::Username( const Username & src )
// {
// }


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Username::~Username()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

// Username &				Username::operator=( Username const & rhs )
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

std::string  Username::execute(Server &server,const string& message, User& liveUser) {
	string welcomeMessage;
	(void)liveUser;
	(void)message;
	(void)server;

	welcomeMessage = "001 dave :Welcome on ft_irc !\r\n"; //can't be user all the time
	return (welcomeMessage);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */