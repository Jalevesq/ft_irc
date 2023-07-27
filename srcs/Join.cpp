#include "../include/Join.hpp"

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

std::string Join::execute(Server &server,const string& message, User& liveUser) {
	string join;
	(void)server;

	join = ":" + liveUser.getNickname() + " " + message + "\r\n";
	return (join);
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */