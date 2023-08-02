#include "../include/Kick.hpp"
#include "../include/Utility.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Kick::Kick()
{
}

// Kick::Kick( const Kick & src )
// {
// }


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Kick::~Kick()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

// Kick &				Kick::operator=( Kick const & rhs )
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

// KICK #Finnish Matthew   
// KICK #Finnish John :Speaking English

string Kick::execute(Server &server,const string& message, User& liveUser) {
	(void)server;
	(void)message;
	(void)liveUser;
	std::vector<string> messageTokens;

	messageTokens = tokenize(message, " ");
	return ("");

}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */