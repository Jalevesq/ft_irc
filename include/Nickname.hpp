#ifndef NICKNAME_HPP
# define NICKNAME_HPP

# include <iostream>
# include <string>
# include "Command.hpp"

using std::string;
using std::cout;
using std::endl;
using std::cerr;

// class Command;

class Nickname : public Command
{

	public:

		Nickname();
		// Nickname( Nickname const & src );
		virtual std::string execute(const std::string& message, User& liveUser);
		~Nickname();

		// Nickname &		operator=( Nickname const & rhs );

	private:

};

#endif /* ******************************************************** NICKNAME_H */