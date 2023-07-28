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

static bool isUserAvailable(const std::string &name){
	(void)name;
	return true;
}

static bool isNotEmptyString(const std::string &str){
 for (int index = 0; str[index]; index++){
		if (str[index] != ' ' )
			return true;
	}
	return false;
}

std::string  Username::execute(Server &server, const string& message, User& liveUser){
	std::vector<std::string> tokens;
	string token, welcomeMessage = "";
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
		welcomeMessage = "461 USER :Not enough parameters\r\n";
	else if (tokens[1].length() > USERLEN)
		welcomeMessage = "005 letpun :User is too long\r\n";
	else if (!isUserAvailable(tokens[1]))
		welcomeMessage = "462 :This user is already taken\r\n";
	else if (tokens[2] != "0" || tokens[3] != "*")
		welcomeMessage = "400 :Wrong character, follow the prototype given in register instruction.\r\n";
	else if (":" + tokens[1] != tokens[4])
		welcomeMessage = "400 :the user is different at the end and at the second place. follow the prototype given in register instruction.\r\n";
	else {
		liveUser.setUsername(tokens[1]);
		liveUser.setIsRegistered(true);
		welcomeMessage = "001 " + liveUser.getNickname() + " :Your are now register. Welcome on ft_irc !\r\n";
	}
	return (welcomeMessage);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */