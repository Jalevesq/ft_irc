#ifndef PASS_HPP
# define PASS_HPP

# include <iostream>
# include <string>
# include "Command.hpp"

using std::string;
using std::cout;
using std::endl;
using std::cerr;

class Pass : public Command
{

	public:

		Pass();
		~Pass();

		// Pass( Pass const & src );
		// Pass &		operator=( Pass const & rhs );
		virtual std::string execute(Server &server,const string& message, User& liveUser);


	private:

};

#endif /* ************************************************************ PASS_H */