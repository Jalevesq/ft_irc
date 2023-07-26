#pragma once
# include <vector>
# include <iostream>
# include <poll.h>
# include <stdexcept>
# include <string>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <unistd.h>
# include <cstdlib>

# include "User.hpp"
# include "Command.hpp"

using std::string;
using std::cout;
using std::endl;
using std::cerr;

#define MAX_USER 99

class Server{
public:
 	Server();
	// Server(const Server &rhs);
	~Server();

	// Server &operator=(const Server &rhs);

	void initServer(char **argv);
	void serverRun();

	const int &getUserCount() const;
	const int &getChannelCount() const;
	const int &getFd() const;

	void setUserCount(int count);
	void setChannelCount(int count);
	void createUser(int &newFd);
	void acceptUser();
	void disconnectUser(int index);
	string	 isCommand(const std::string &message, const int &fd, const int &index);
	void handleMessage(const std::string &message, const int &fd, const int &index);


private:
 Command allCommand;
 std::vector<User *> userVector_;
 std::vector<struct pollfd> poll_;
 int userCount_;
 int channelCount_;
 struct sockaddr_in address_;
 socklen_t addressLength_;
 //std::string password_;
};