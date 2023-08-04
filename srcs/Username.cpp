#include "../include/Username.hpp"
#include "../include/Utility.hpp"
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

string  Username::execute(Server &server, const string& message, User& liveUser){
	(void)server;
	string username, realName;
	std::vector<string> tokenMessage = tokenize(message, " ");

	if (liveUser.getIsRegister() == true) {
		return ("463 PRIVMSG :You're already register.\r\n");
	}

	if (tokenMessage.size() < 5) {
		return ("461 USER :Not enough parameters\r\n");
	}
	username = tokenMessage[1];
	if (username.find("\t\n\v\f\r @+",0) != string::npos) {
		return("400 :Forbidden char in username.\r\n");
	} else if (username.length() > USERLEN ) {
		return("005 letpun :User is too long\r\n");
	}
	if (tokenMessage[2].size() > 1 || tokenMessage[2][0] != '0') {
		return ("400 :Wrong character, suppose to be '0'. follow the prototype given in register instruction.\r\n");
	} else if (tokenMessage[3].size() > 1 || tokenMessage[3][0] != '*') {
		return("400 :Wrong character, suppose to be '*', follow the prototype given in register instruction.\r\n");
	}
	size_t pos = message.find(":");
	if (pos == string::npos) {
		return ("461 PRIVMSG :Bad format of command. Need ':' before real name to execute.\r\n");	
	}
	realName = message.substr(pos + 1);
	if (realName.empty())
		return ("400 :No realname given\r\n");
	if (realName.find("\t\n\v\f\r") != string::npos) {
		return ("400 :Forbidden char in real name.\r\n");
	}
	liveUser.setUsername(username);
	return ("");
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */