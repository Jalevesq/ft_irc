#ifndef PING_HPP
# define PING_HPP

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

class Ping : public Command
{

	public:

		Ping();
		~Ping();
		// Ping( Ping const & src );
		// Ping &		operator=( Ping const & rhs );
	
		virtual std::string execute(Server &server,const string& message, User& liveUser);

	private:

};

#endif /* ************************************************************ PING_H */