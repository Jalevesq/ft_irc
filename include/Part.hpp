#ifndef PART_HPP
# define PART_HPP

# include <iostream>
# include <string>
# include "Command.hpp"

using std::string;
using std::cout;
using std::endl;
using std::cerr;

class Part : public Command
{

	public:

		Part();
		~Part();

		virtual string execute(Server &server,const string& message, User& liveUser);
		// Part( Part const & src );
		// Part &		operator=( Part const & rhs );
	private:

};

#endif /* ************************************************************ PART_H */