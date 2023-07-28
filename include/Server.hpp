#pragma once
# include <map>
# include <vector>
# include <set>
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


// class Command;
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
	void disconnectUser(int index, int fd);

	// Eveything related to message recieved
	void handleMessage(const std::string &message, User& liveUser);
	const string Auth(Command *cmd, User &liveUser, const string &argument);


	// nicknameList_ manipulator
	void addNickname(const string& nickname);
	bool checkNickname(const string &nickname) const;
	void removeNickname(const string& nickname);

private:
	std::map<int, User *> listUser_;
	std::map<std::string, Command *> commandList_;
	std::set<string> usernameList_;
	std::set<string> nicknameList_;
	std::vector<struct pollfd> poll_;
	struct sockaddr_in address_;
	CommandFactory factory_;
	int userCount_;
	int channelCount_;
	//std::string password_;
};