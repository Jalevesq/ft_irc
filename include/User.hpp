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
		User();
		~User();
		const string& getNickname() const;
		const string& getUsername() const;
		const bool& getOperator() const;
		const int& getFdSocket() const;

		void setNickname(const string &newNickname);
		void setUsername(const string &newUsername);
		void setOperator(const bool &newOperator);
		void setfdSocket(const int &fd);
		// User( User const & src  );

		// User &		operator=( User const & rhs );

	private:
		string	nickname_;
		string	username_;
		bool	operator_;
		int		fdSocket_;
};

// std::ostream &			operator<<( std::ostream & o, User const & i );

#endif /* ************************************************************ USER_H */