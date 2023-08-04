#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include <string>
# include <poll.h>
# include <set>
# include <unistd.h>
# include "Channel.hpp"

using std::string;
using std::cout;
using std::endl;

# define PASS 0
# define AUTH 1

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
		const string& getMessage() const;
	
		const bool& getIsPass() const;
		void setIsPass(const bool &setPass);
	
		void setIsRegister(const bool &setRegister);
		const bool& getIsRegister() const;

		void setNickname(const string &newNickname);
		void setUsername(const string &newUsername);
		void setOperator(const bool &newOperator);
		void setfdSocket(const int &fd);

		void appendMessage(const string& appendMessage);
		void clearMessage();

		void addChannelUser(const string &name);
		void removeChannelUser(const string &name);
		std::set<string> getChannelSet();
		// User( User const & src  );
		// User &		operator=( User const & rhs );
		unsigned long int getSizeInviteList();
		std::vector<Channel *> returnInviteList();
		void addChannelInInviteList(Channel *channel);
		void removeChannelInInviteList(Channel *channel);
		void clearChannelInInviteList();


	private:
		string	message_;
		string	nickname_;
		string	username_;
		bool	operator_;
		bool	isRegistered_[2];
		int		fdSocket_;
		std::vector<Channel *> inviteInChannel_;
		std::set<string> channels_;
};

#endif /* ************************************************************ USER_H */