#ifndef JOIN_HPP
# define JOIN_HPP

# include <iostream>
# include <string>
# include "Command.hpp"

using std::string;
using std::cout;
using std::endl;
using std::cerr;

class Command;
// class Server;

class Join : public Command
{

	public:

		Join();
		~Join();
		// Join( Join const & src );
		// Join &		operator=( Join const & rhs );
	
		// need to set permision and all that, far from done at all
		virtual string execute(Server &server,const string& message, User& liveUser);


	private:

};


#endif /* ************************************************************ JOIN_H */