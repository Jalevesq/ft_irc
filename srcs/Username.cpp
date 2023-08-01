#include "../include/Username.hpp"
#include "../include/Utility.hpp"

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

// static bool isNotEmptyString(const std::string &str){
//  for (int index = 0; str[index]; index++){
// 		if (str[index] != ' ' )
// 			return true;
// 	}
// 	return false;
// }

string  Username::execute(Server &server, const string& message, User& liveUser){
	std::vector<std::string> tokens;
	string token, finalMessage = "";
	size_t index = 0;
  size_t end = message.find(" ");
	(void)server;

	while (end != std::string::npos){
		token = message.substr(index, end - index);
		if (isNotEmptyString(token) && token.find(" ") == std::string::npos)
			tokens.push_back(token);
		index = end + 1;
		end = message.find(" ", index);
	}
	token = message.substr(index);
	if (isNotEmptyString(token) && token.find(" ") == std::string::npos)
		tokens.push_back(token);

	if (tokens.size() != 5)
		finalMessage = "461 USER :Not enough parameters\r\n";
	else if (tokens[1].length() > USERLEN)
		finalMessage = "005 letpun :User is too long\r\n";
	else if (tokens[2] != "0" || tokens[3] != "*")
		finalMessage = "400 :Wrong character, follow the prototype given in register instruction.\r\n";
	else {
		liveUser.setUsername(tokens[1]);
		finalMessage = ""; // que renvoyer ?
	}
	// else if (":" + tokens[1] != tokens[4])
		// finalMessage = "400 :the user . follow the prototype given in register instruction.\r\n";

	// SI le username fail, how tf c'est possible de renvoyer la commande quand on se co avec weechat ? Déconnecter la personne si le user fail ou la laisser se démerder?

	return (finalMessage);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */