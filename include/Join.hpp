#ifndef JOIN_HPP
# define JOIN_HPP

# include <iostream>
# include <string>
# include <vector>
# include "Command.hpp"

using std::string;
using std::cout;
using std::endl;
using std::cerr;

class Join : public Command
{

	public:

		Join();
		~Join();
		// Join( Join const & src );
		// Join &		operator=( Join const & rhs );
	
		// need to set permision and all that, far from done at all
		virtual string execute(Server &server,const string& message, User& liveUser);


		void tokenizeJoin(const string &message);
		const std::string createChannel(Server &server, User &liveUser) const;


	private:
		std::vector<string> tokens_;
};


#endif /* ************************************************************ JOIN_H */