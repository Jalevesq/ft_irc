#ifndef JOIN_HPP
# define JOIN_HPP

# include <iostream>
# include <string>
# include "Command.hpp"

using std::string;
using std::cout;
using std::endl;
using std::cerr;

// class Command;

class Join : public Command
{

	public:

		Join();
		// Join( Join const & src );
	
		// need to set permision and all that, far from done at all
		virtual std::string execute(const std::string& message, User& liveUser);
		~Join();

		// Join &		operator=( Join const & rhs );

	private:

};


#endif /* ************************************************************ JOIN_H */