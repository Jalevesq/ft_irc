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
# include "Pass.hpp"
# include "CommandFactory.hpp"
# include "Channel.hpp"

#define BUFFER_SIZE 1024
#define MAX_USER 25
#define MAX_CHANNEL 35
#define MAX_CHANNEL_PER_USER 10
#define MAX_USER_INVITE_LIST 5
#define OPER_PASSWORD "bozo.com"

using std::string;
using std::cout;
using std::endl;
using std::cerr;

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
	int getChannelCount() const;
	const int &getFd() const;
	Channel *getChannel(const std::string &name);
	const string& getPassword() const;

	// Everything related to user
	User *doesUserExist(const std::string &name);
	void createUser(int &newFd);
	void acceptUser();
	void disconnectUser(int index, int fd);
	void sendUserToTheShadowRealm(int fd) const;

	// Eveything related to message recieved
	void handleMessage(const std::string &message, User& liveUser);
	const string Auth(Command *cmd, User &liveUser, const string &argument);


	// nicknameList_ manipulator
	void addNickname(const string& nickname);
	bool checkNickname(const string &nickname) const;
	void removeNickname(const string& nickname);

	//Channels
	bool doesChannelExist(const std::string &name);
	void addChannel(const std::string &name, Channel *channel);
	void removeChannel(const std::string &name);
	User *getUserPointer(int fd);

private:
	std::map<int, User *> listUser_;
	std::map<std::string, Command *> commandList_;
	std::map<std::string, Channel *> channels_;
	// std::vector<User *> userVector_;
	std::set<string> nicknameList_;
	std::vector<struct pollfd> poll_;
	int userCount_;
	struct sockaddr_in address_;
	CommandFactory factory_;
	string password_;
};