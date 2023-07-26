#ifndef USERNAME_HPP
# define USERNAME_HPP

# include <iostream>
# include <string>
# include "Command.hpp"

using std::string;
using std::cout;
using std::endl;
using std::cerr;

// class Command;

class Username : public Command
{

	public:

		Username();
		// Username( Username const & src );
		~Username();
		virtual std::string execute(const std::string& message, User& liveUser);
		Username &		operator=( Username const & rhs );

	private:

};

#endif /* ******************************************************** USERNAME_H */