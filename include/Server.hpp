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

# include "Join.hpp"
# include "Nickname.hpp"
# include "Ping.hpp"
# include "Username.hpp"
# include "CommandFactory.hpp"

using std::string;
using std::cout;
using std::endl;
using std::cerr;

#define MAX_USER 99

class Server{
public:
 	Server();
	~Server();
	// Server(const Server &rhs);
	// Server &operator=(const Server &rhs);


	// Main function
	void initServer(char **argv);
	void serverRun();

	// Getter
	const int &getUserCount() const;
	const int &getChannelCount() const;
	const int &getFd() const;

	// Setter
	void setUserCount(int count);
	void setChannelCount(int count);

	// Everything related to user
	void createUser(int &newFd);
	void acceptUser();
	void disconnectUser(int index);

	// Eveything related to message recieved
	void handleMessage(const std::string &message, const int &fd, User& liveUser);
	const string isCommand(const std::string &message) const;


private:
	std::map<std::string, Command *> commandList_;
	std::vector<User *> userVector_;
	std::vector<struct pollfd> poll_;
	int userCount_;
	int channelCount_;
	struct sockaddr_in address_;
	socklen_t addressLength_;
	CommandFactory factory_;
	//std::string password_;
};