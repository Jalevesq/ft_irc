#include "../include/Ping.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Ping::Ping()
{
	this->commandName_ = PING;
}

// Ping::Ping( const Ping & src )
// {
// }


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Ping::~Ping()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

// Ping &				Ping::operator=( Ping const & rhs )
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

std::string Ping::execute(const std::string& message, User& liveUser) {
	string pingMessage;
	(void)liveUser;

	pingMessage = "PONG " + message.substr(5) + "\r\n"; // think it works?
	return (pingMessage);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */