#ifndef INVITE_HPP
# define INVITE_HPP

# include <iostream>
# include <string>
# include "Command.hpp"


using std::string;
using std::cout;
using std::endl;
using std::cerr;

class Invite : public Command
{

	public:

		Invite();
		~Invite();
		virtual string execute(Server &server,const string& message, User& liveUser);
		// Invite( Invite const & src );
		// Invite &		operator=( Invite const & rhs );

	private:

};

#endif /* ********************************************************** INVITE_H */