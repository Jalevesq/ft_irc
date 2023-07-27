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

std::string Nickname::execute(Server &server,const string& message, User& liveUser) {
    string nickMessage;
    string newNickname;
    (void)server;

    // Add protection to check if newNickname is valid (already in use? not authorized char?)
    newNickname = message.substr(5);
    if (newNickname.find_first_of(":") != string::npos) {
        newNickname = newNickname.substr(1);
    }
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

    if (newNickname.find_first_of("&:#\t\n\v\f\r ", 0) != string::npos) {
        nickMessage = "432 '"  + newNickname + "' :Erroneus nickname\r\n";
    } else {
        nickMessage = ":" + liveUser.getNickname() + " NICK " + ":" + newNickname + "\r\n";
        liveUser.setNickname(newNickname);
    }

    // ** Problem with the nickname recieve when there is ':' in nickname **
    // Because: quand un nickanme contient :, la formule que weechat envoie passe de: NICK fuck a NICK :fuc:k. Donc le premier substr devient mauvais. if find_first_of : ?

    // Error nickname
    // ERR_NONICKNAMEGIVEN (431) Returned when a nickname parameter is expected for a command but isn’t given.
    // ERR_ERRONEUSNICKNAME (432) Returned when a NICK command cannot be successfully completed as the desired nickname contains characters that are disallowed by the server. See the NICK command for more information on characters which are allowed in various IRC servers. The text used in the last param of this message may vary.
    // ERR_NICKNAMEINUSE (433) Returned when a NICK command cannot be successfully completed as the desired nickname is already in use on the network. The text used in the last param of this message may vary.


    return nickMessage;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */