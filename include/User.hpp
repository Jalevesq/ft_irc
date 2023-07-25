#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include <string>
# include <poll.h>
# include <unistd.h>
using std::string;
using std::cout;
using std::endl;

class User
{

	public:
		User(string newNickname, string newUsername, int newFdSocket);
		~User();
		const string& getNickname() const;
		const string& getUsername() const;
		const bool& getOperator() const;
		const int& getFdSocket() const;

		void setNickname(string newNickname);
		void setUsername(string newUsername);
		void setOperator(bool newOperator);
		// User( User const & src  );

		// User &		operator=( User const & rhs );

	private:
		User();
		string	nickname_;
		string	username_;
		bool	operator_;
		int		fdSocket_;
};

// std::ostream &			operator<<( std::ostream & o, User const & i );

#endif /* ************************************************************ USER_H */