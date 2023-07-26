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
	
		virtual std::string execute(const std::string& message, User& liveUser) = 0;
		// const string parseCommand(const string& message, const string& command, User& liveUser);
		// const string isCommand(const std::string &message) const;

		// Command( Command const & src );
		// Command &		operator=( Command const & rhs );

	private:

};

#endif /* ********************************************************* COMMAND_H */