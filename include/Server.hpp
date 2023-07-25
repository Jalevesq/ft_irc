#pragma once
#include <vector>
#include <iostream>
#include <poll.h>

#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>


#define MAX_USER 10

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

private:
 int userCount_;
 int channelCount_;
 struct pollfd poll_[MAX_USER + 1];
 struct sockaddr_in address_;
 socklen_t addressLength_;
 //std::string password_;
};