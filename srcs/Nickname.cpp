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

    // Find the position of the first non-whitespace character
    size_t firstNonSpace = newNickname.find_first_not_of(" \r\n");
    if (firstNonSpace != std::string::npos) {
        // Find the position of the last non-whitespace character
        size_t lastNonSpace = newNickname.find_last_not_of(" \r\n");
        if (lastNonSpace != std::string::npos) {
            // Extract the trimmed nickname using substr
            newNickname = newNickname.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
        } else {
            // If the last non-whitespace character is not found, set the newNickname to an empty string
            newNickname = "";
        }
    } else {
        // If the first non-whitespace character is not found, set the newNickname to an empty string
        newNickname = "";
    }

    nickMessage = ":" + liveUser.getNickname() + " NICK " + ":" + newNickname + "\r\n";
    liveUser.setNickname(newNickname);
    return nickMessage;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */