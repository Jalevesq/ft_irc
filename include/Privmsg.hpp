#ifndef PRIVMSG_HPP
# define PRIVMSG_HPP

# include <iostream>
# include <string>
# include "Command.hpp"

# define DEST 0
# define MSG 1

using std::string;
using std::cout;
using std::endl;
using std::cerr;

class Privmsg : public Command
{

	public:

		Privmsg();
		~Privmsg();

		// Privmsg( Privmsg const & src );
		// Privmsg &		operator=( Privmsg const & rhs );
		virtual std::string execute(Server &server,const string& message, User& liveUser);
		bool isUserInChannel(User& liveUser, string &destination);
		string channelMessage(User &liveUser, std::vector<string>& infoMessage, Server& server);
		string privateMessage(User &liveUser, std::vector<string>& infoMessage, Server& server);

	private:

};

#endif /* ********************************************************* PRIVMSG_H */