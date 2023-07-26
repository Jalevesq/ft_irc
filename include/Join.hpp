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
		virtual std::string execute(const std::string& message, User& liveUser) {
			(void)message;
			(void)liveUser;
			return "BALLS fuck";
		};
		~Join();

		// Join &		operator=( Join const & rhs );

	private:

};


#endif /* ************************************************************ JOIN_H */