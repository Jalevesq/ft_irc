#ifndef PRIVMSG_HPP
# define PRIVMSG_HPP

# include <iostream>
# include <string>
# include "Command.hpp"

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

	private:

};

#endif /* ********************************************************* PRIVMSG_H */