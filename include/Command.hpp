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

class Command
{

	public:
	    typedef const std::string (Command::*MemberFunction)(const std::string&, const User&);
		Command();
		// Command( Command const & src );
		~Command();

		const string isCommand(const string &message) const;
		const string parseCommand(const string& message, const string& command, const User& liveUser);

		const string nickCommand(const string& message, const User& liveUser);
		const string joinCommand(const string& message, const User& liveUser);
		const string userCommand(const string& message, const User& liveUser);
		const string pingCommand(const string& message, const User& liveUSer);
		// Command &		operator=( Command const & rhs );

	private:
		// instead of int, put function prototype
	    std::map<std::string, MemberFunction> _commandList;

};

#endif /* ********************************************************* COMMAND_H */