#ifndef NICKNAME_HPP
# define NICKNAME_HPP

# include <iostream>
# include <string>
# include <set>
# include "Command.hpp"

using std::string;
using std::cout;
using std::endl;
using std::cerr;

// class Command;

class Nickname : public Command
{

	public:

		Nickname();
		~Nickname();
		// Nickname( Nickname const & src );
		// Nickname &		operator=( Nickname const & rhs );

		virtual std::string execute(const std::string& message, User& liveUser);
		void addNickname(const string& newNickname);
		void removeNickname(const string& rmNickname);
	private:
		std::set<string> nicknameList_;

};

#endif /* ******************************************************** NICKNAME_H */