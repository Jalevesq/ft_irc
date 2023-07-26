#include "../include/Nickname.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Nickname::Nickname()
{
	this->commandName_ = NICK;
}

// Nickname::Nickname( const Nickname & src )
// {
// }


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Nickname::~Nickname()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

// Nickname &				Nickname::operator=( Nickname const & rhs )
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

std::string Nickname::execute(const std::string& message, User& liveUser) {
	string nickMessage;
	string newNickname;
	
	// Add protection to check if newNickname is valid
	newNickname = message.substr(5);
	nickMessage = ":" + liveUser.getNickname() + " NICK " + ":" + newNickname + "\r\n";
	// cout << "newNickname: '" << newNickname << "'" << endl; 
	liveUser.setNickname(newNickname);
	return (nickMessage);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */