#ifndef USERNAME_HPP
# define USERNAME_HPP

# include "Server.hpp"
# include <iostream>
# include <string>
# include "Command.hpp"

using std::string;
using std::cout;
using std::endl;
using std::cerr;

// class Command;
// class Server;

class Username : public Command
{

	public:

		Username();
		~Username();
		// Username( Username const & src );
		// Username &		operator=( Username const & rhs );
		virtual std::string execute(Server &server,const string& message, User& liveUser);

	private:

};

#endif /* ******************************************************** USERNAME_H */