#include "../include/Nickname.hpp"
#include "../include/Server.hpp"
#include "../include/Utility.hpp"
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
// NICK Wiz
// :WiZ NICK Kilroy  

std::string Nickname::execute(Server &server,const string& message, User& liveUser) {
    string nickMessage;
    string newNickname;
	std::vector<string> tokensMessage = tokenize(message, " ");

	if (tokensMessage.size() <= 1) {
		return ("431 :No nickname given\r\n");
	}

	size_t pos = message.find(" ");
	newNickname = message.substr(pos + 1);
	if (newNickname.find_first_of("\t\n\v\f\r ", 0) != string::npos || newNickname.empty()
		|| newNickname[0] == '#' || newNickname[0] == '&' || newNickname[0] == ':') {
        nickMessage = "432 '"  + newNickname + "' :Erroneus nickname\r\n";
	} else if (server.checkNickname(newNickname)) {
		nickMessage = "433 '" + newNickname + "' :Nickname is already in use\r\n";
    } else if (newNickname.length() > 10) {
		nickMessage = "432 '" + newNickname + "' :Nickname too long (> 10 char)\r\n"; 
	} else {
		string liveNickname = liveUser.getNickname();
		if (liveNickname.empty())
			liveNickname = newNickname;
        nickMessage = ":" + liveNickname + " NICK " + ":" + newNickname + "\r\n";
		if (server.checkNickname(liveNickname))
			server.removeNickname(liveNickname);
		server.addNickname(newNickname);
        liveUser.setNickname(newNickname);
        sendChannelNickChange(server, liveNickname, liveUser); //Broadcast to other users
    }

    return nickMessage;
}

void Nickname::sendChannelNickChange(Server &server, const string &oldNick, User &liveUser){
  std::set<std::string> set = liveUser.getChannelSet();
  if (set.size() == 0)
      return;
  std::set<std::string>::iterator it = set.begin();
  for (; it != set.end(); it++){
      Channel *channel = server.getChannel(*it);
      channel->sendNameChange(&liveUser, oldNick);
  }
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */