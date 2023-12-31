#ifndef JOIN_HPP
# define JOIN_HPP

# include <iostream>
# include <string>
# include <vector>
# include <map>
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
	
		virtual string execute(Server &server,const string& message, User& liveUser);
		void	createChannel(Server &server, User &liveUser,  std::map<string, string>::iterator tokens) const;
		string	loop_through_map(std::map<string, string> &channelAndKey,User& liveUser, Server &server);

	private:
};


#endif /* ************************************************************ JOIN_H */