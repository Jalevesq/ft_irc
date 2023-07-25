#include "../include/Server.hpp"
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

using std::string;
using std::cout;
using std::endl;
using std::cerr;

Server::Server(): userCount_(0), channelCount_(0){
	struct pollfd listennerPoll;
	listennerPoll.events = POLLIN;
	listennerPoll.fd = -1;
	this->poll_.push_back(listennerPoll);
}

Server::~Server(){ 
	for (int i = 0; i < this->userCount_; i++)
		delete this->userVector_[i];
	close(poll_[0].fd); 
}

void Server::initServer(char **argv){
	int ret;
	std::string port = argv[1];
	if (port.empty())
		throw std::runtime_error("Port provided is empty");
	if (port.find_first_not_of("0123456789") != port.npos || port.size() != 4)
		throw std::runtime_error("Port provided is invalid");
	int fdSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (fdSocket == -1)
		throw std::runtime_error("Socket couldn't be initialize");
  address_.sin_port = htons(stoi(port));
  address_.sin_family = AF_INET;
  address_.sin_addr.s_addr = htonl(INADDR_ANY);
	fcntl(fdSocket, F_SETFL, O_NONBLOCK);
	ret = bind(fdSocket, (struct sockaddr*)&address_, sizeof(address_));
	if (ret == -1)
		throw std::runtime_error("Bind failure"); // check later to close fd maybe?
	ret = listen(fdSocket, MAX_USER);
	if (ret == -1)
		throw std::runtime_error("Listen failure"); // check later to close fd maybe?
	poll_[0].fd = fdSocket;
	addressLength_ = sizeof(address_);
}

void Server::serverRun()
{
	char buffer[1024];
	while (true)
	{
		poll(poll_.data(), userCount_ + 1, 100);
		//	throw std::runtime_error("Poll failure"); // fix later
		if (poll_[0].revents & POLLIN){ // if more than max user fix later
			int newFd = accept(poll_[0].fd, (struct sockaddr *)&address_, &addressLength_);
			if (newFd == -1)
				throw std::runtime_error("Accept failure"); // fix later
			std::cout << "New connection accepted, socket fd: " << newFd << std::endl;
			userCount_++;
			createUser(newFd);
			string welcomeMessage = "001 user" + std::to_string(userCount_) + " :Welcome on ft_irc !\r\n"; // fix later
			send(newFd, welcomeMessage.c_str(), welcomeMessage.size(), 0);
		}
		for (int i = 1; i <= userCount_; i++){
			if (poll_[i].revents & (POLLHUP | POLLERR | POLLNVAL)){
				poll_.erase(poll_.begin() + i);
				delete userVector_[i - 1];
				userVector_.erase(userVector_.begin() + (i - 1));
				userCount_--;
				cout << "user " << i << " disconnected" << endl;
			}
			else if (poll_[i].revents & POLLIN){
				int ret = recv(poll_[i].fd, buffer, 1024, MSG_DONTWAIT);
				if (ret == -1) {
					cout << errno << endl;
				throw std::runtime_error("Recv failure"); // fix later
				}
				else{
					buffer[ret] = '\0';
					std::cout << "Received from socket fd " << poll_[i].fd << ": " << buffer;
				}
			}
		}
	}
}

void Server::createUser(int& newFd){
	struct pollfd newPoll;
	newPoll.fd = newFd;
	newPoll.events = POLLIN;
	newPoll.revents = 0;
	this->poll_.push_back(newPoll);

	User *newUser = new User("user", "user", newFd);
	this->userVector_.push_back(newUser);
}

const int &Server::getUserCount() const { return userCount_; }

const int &Server::getChannelCount() const { return channelCount_; }

const int &Server::getFd() const { return poll_[0].fd; }

void Server::setUserCount(int count){ userCount_ += count; }

void Server::setChannelCount(int count){ channelCount_ += count; }