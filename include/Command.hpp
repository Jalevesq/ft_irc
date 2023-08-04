#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "User.hpp"
# include <iostream>
# include <string>
# include <map>

using std::string;
using std::cout;
using std::endl;
using std::cerr;

# define NICK "NICK"
# define JOIN "JOIN"
# define USER "USER"
# define PING "PING"
# define PASSW "PASS"
# define PART "PART"
# define PRIV "PRIVMSG"
# define TOPIC "TOPIC"
# define KICK "KICK"
# define MODE "MODE"
# define OPER "OPER"
# define INVITE "INVITE"

class Server;

class Command
{

	public:
		Command();
		virtual ~Command();
	
		virtual string execute(Server &server, const string& message, User& liveUser) = 0;
		virtual const string& getName();

		// Command( Command const & src );
		// Command &		operator=( Command const & rhs );

	protected:
		string commandName_;

};

#endif /* ********************************************************* COMMAND_H */