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
		virtual std::string execute(const std::string& message, User& liveUser) {
			(void)message;
			(void)liveUser;
			return "fuck PING";
		};
		// Ping( Ping const & src );
		// Ping &		operator=( Ping const & rhs );

	private:

};

#endif /* ************************************************************ PING_H */