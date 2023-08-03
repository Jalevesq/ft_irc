#ifndef OPER_HPP
# define OPER_HPP

# include <iostream>
# include <string>
# include "Command.hpp"

using std::string;
using std::cout;
using std::endl;
using std::cerr;
class Oper : public Command
{

	public:

		Oper();
		~Oper();

		virtual string execute(Server &server,const string& message, User& liveUser);
		// Oper( Oper const & src );
		// Oper &		operator=( Oper const & rhs );

	private:

};

#endif /* ************************************************************ OPER_H */