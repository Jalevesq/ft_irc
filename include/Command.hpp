#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <iostream>
# include <string>
# include <map>
# include "User.hpp"

using std::string;
using std::cout;
using std::endl;
using std::cerr;

# define NICK "NICK"
# define JOIN "JOIN"
# define USER "USER"
# define PING "PING"
# define CMD_NBR 4

class Command
{

	public:
		Command();
		virtual ~Command();
	
		virtual string execute(const string& message, User& liveUser) = 0;
		virtual const string& getName();

		// Command( Command const & src );
		// Command &		operator=( Command const & rhs );

	protected:
		string commandName_;

};

#endif /* ********************************************************* COMMAND_H */