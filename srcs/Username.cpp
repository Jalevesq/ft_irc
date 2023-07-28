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
		if (str[index] != ' ' && str[index] != '\0')
			return true;
	}
	return false;
}

std::string  Username::execute(Server &server, const string& message, User& liveUser){
	std::vector<std::string> tokens;
	std::string token;
	size_t index = 0;
  size_t end = message.find(" ");
	(void)liveUser;
	(void)server;

	while (end != std::string::npos){
		token = message.substr(index, end - index);
		if (isNotEmptyString(token) && token.find(" ") == std::string::npos)
			tokens.push_back(token);
		// else
		// 	return "BOZO";
		index = end + 1;
		end = message.find(" ", index);
	}
	token = message.substr(index);
	if (isNotEmptyString(token) && token.find(" ") == std::string::npos)
		tokens.push_back(token);
	// else
	// 	return "BOZO";
	if (tokens.size() != 5)
		return "461 USER :Not enough parameters\r\n";
	if (tokens[1].length() > USERLEN)
		return "005 letpun :User is too long\r\n";
	if (!isUserAvailable(tokens[1]))
		return "462 :This user is already taken\r\n";
	if (tokens[2] != "0" || tokens[3] != "*")
		return "wrong character\r\n";
	std::string delim = ":";
	if (":" + tokens[1] != tokens[4])
		return "wtf are you doing\r\n";
	// string welcomeMessage = "001 " + liveUser.getNickname() + " :Welcome on ft_irc !\r\n";
	liveUser.setUsername(tokens[1]);
	return "Bozo\r\n";
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */