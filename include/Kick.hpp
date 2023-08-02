#ifndef KICK_HPP
# define KICK_HPP

# include <iostream>
# include <string>
# include "Command.hpp"


using std::string;
using std::cout;
using std::endl;
using std::cerr;

class Kick : public Command
{

	public:

		Kick();
		~Kick();

		virtual string execute(Server &server,const string& message, User& liveUser);
		// Kick( Kick const & src );
		// Kick &		operator=( Kick const & rhs );

	private:

};

#endif /* ************************************************************ KICK_H */