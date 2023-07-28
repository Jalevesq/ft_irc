#ifndef NICKNAME_HPP
# define NICKNAME_HPP

# include <iostream>
# include <string>
# include <set>
# include "Command.hpp"

using std::string;
using std::cout;
using std::endl;
using std::cerr;

class Nickname : public Command
{

	public:

		Nickname();
		~Nickname();
		// Nickname( Nickname const & src );
		// Nickname &		operator=( Nickname const & rhs );

		virtual string execute(Server &server,const string& message, User& liveUser);
	private:

};

#endif /* ******************************************************** NICKNAME_H */