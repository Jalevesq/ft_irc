#ifndef PING_HPP
# define PING_HPP

# include <iostream>
# include <string>
# include "Command.hpp"

using std::string;
using std::cout;
using std::endl;
using std::cerr;

// class Command;

class Ping : public Command
{

	public:

		Ping();
		~Ping();
		// Ping( Ping const & src );
		// Ping &		operator=( Ping const & rhs );
	
		virtual std::string execute(const std::string& message, User& liveUser);

	private:

};

#endif /* ************************************************************ PING_H */