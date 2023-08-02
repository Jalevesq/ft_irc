#include "../include/Nickname.hpp"
#include "../include/Server.hpp"

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

	newNickname = message.substr(4);
    if (newNickname.empty() || (newNickname.size() == 1 && newNickname[0] == ' ')){
		nickMessage = "431 :No nickname given\r\n"; 
		return (nickMessage);
	}

    size_t firstNonSpace = newNickname.find_first_not_of(" ");
    if (firstNonSpace != std::string::npos) {
        size_t lastNonSpace = newNickname.find_last_not_of("\r\n");
        if (lastNonSpace != std::string::npos) {
            newNickname = newNickname.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
        } else {
            newNickname = "";
        }
    } else {
        newNickname = "";
    }

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

    // Error nickname
    // ERR_NONICKNAMEGIVEN (431) Returned when a nickname parameter is expected for a command but isn’t given.
    // ERR_ERRONEUSNICKNAME (432) Returned when a NICK command cannot be successfully completed as the desired nickname contains characters that are disallowed by the server. See the NICK command for more information on characters which are allowed in various IRC servers. The text used in the last param of this message may vary.
    // ERR_NICKNAMEINUSE (433) Returned when a NICK command cannot be successfully completed as the desired nickname is already in use on the network. The text used in the last param of this message may vary.

	// Mettre une protection pour les nickname trop long
	// Que faire avec le /nick -all <name> ? Weechat le gère tout seul?

	// Quand ':user' renvoie '::user'. why ?

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