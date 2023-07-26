#include "../include/Server.hpp"

Server::Server(): userCount_(0), channelCount_(0){
	struct pollfd listennerPoll;
	listennerPoll.events = POLLIN;
	listennerPoll.fd = -1;
	this->poll_.push_back(listennerPoll);

	this->commandList_[NICK] = new Nickname;
	this->commandList_[JOIN] = new Join;
	this->commandList_[USER] = new Username;
	this->commandList_[PING] = new Ping;
}

Server::~Server(){ 
	for (int i = 0; i < this->userCount_; i++)
		delete this->userVector_[i];
	close(poll_[0].fd); 
	std::map<string, Command *> ::iterator it;

	it = this->commandList_.begin();
	for (; it != this->commandList_.end(); it++) {
		delete it->second;
	}
}

//////////////////////////////////////////////////////////////////////////////
//	   Init Socket, bind it with port & init our listenner to connection	 //
//////////////////////////////////////////////////////////////////////////////

void Server::initServer(char **argv){
	int ret;
	int fdSocket;
	std::string port = argv[1];
	if (port.empty())
		throw std::runtime_error("Port provided is empty");
	if (port.find_first_not_of("0123456789") != port.npos || port.size() != 4)
		throw std::runtime_error("Port provided is invalid");
	fdSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (fdSocket == -1)
		throw std::runtime_error("Socket couldn't be initialize");
	this->address_.sin_port = htons(atoi(port.c_str())); //if this doesn't compile on mac put stoi instead
	this->address_.sin_family = AF_INET;
	this->address_.sin_addr.s_addr = htonl(INADDR_ANY);
	fcntl(fdSocket, F_SETFL, O_NONBLOCK);
	ret = bind(fdSocket, (struct sockaddr*)&address_, sizeof(address_));
	if (ret == -1){
		close(fdSocket);
		throw std::runtime_error("Bind failure"); // check later to close fd maybe?
	}
	ret = listen(fdSocket, MAX_USER);
	if (ret == -1){
		close(fdSocket);
		throw std::runtime_error("Listen failure"); // check later to close fd maybe?
	}
	this->poll_[0].fd = fdSocket;
	this->addressLength_ = sizeof(address_);
}

//////////////////////////////////////////////
//	   Main loop that handle everything   	//
//////////////////////////////////////////////

void Server::serverRun()
{
	char buffer[1024];
	while (true)
	{
		poll(this->poll_.data(), this->userCount_ + 1, 100);
		//	throw std::runtime_error("Poll failure"); // fix later
		if (this->poll_[0].revents & POLLIN)
			acceptUser();
		for (int i = 1; i <= userCount_; i++){
			if (this->poll_[i].revents & (POLLHUP | POLLERR | POLLNVAL)){
				cout << "user " << (poll_[i].fd - 3) << " disconnected" << endl;
				disconnectUser(i);
			}
			else if (poll_[i].revents & POLLIN){
				int ret = recv(poll_[i].fd, buffer, 1024, MSG_DONTWAIT);
				if (ret == -1)
					throw std::runtime_error("Recv failure"); // fix later. Disconnect only the user that has a problem ? disconnectUser(i) ?
				buffer[ret] = '\0';
				handleMessage(buffer, poll_[i].fd, i);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////
//	   Deleting user because 'Disconnect' signal recieve from fd     //
///////////////////////////////////////////////////////////////////////

void Server::disconnectUser(int index) {
	this->poll_.erase(poll_.begin() + index);
	delete this->userVector_[index - 1];
	this->userVector_.erase(userVector_.begin() + (index - 1));
	this->userCount_--;
}

//////////////////////////////////////
//	   Accept & Create new User   	//
//////////////////////////////////////

void Server::acceptUser(){
	int newFd = accept(poll_[0].fd, (struct sockaddr *)&address_, &addressLength_);
	if (newFd == -1)
		throw std::runtime_error("Accept failure"); // fix later
	std::cout << "New connection accepted, socket fd: " << newFd  << ". User ID: " << (newFd - 3) << std::endl;
	userCount_++;
	createUser(newFd);
	// string welcomeMessage = "001 user :Welcome on ft_irc !\r\n";
	// send(newFd, welcomeMessage.c_str(), welcomeMessage.size(), 0);
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

//////////////////////////////////////////////////////////////////////
//	   Handle each message. Is it a command or a normal message?  	//
//////////////////////////////////////////////////////////////////////

void Server::handleMessage(const std::string &message, const int &fd, const int &index) {
	string command = "";
	string finalMessage = "";
	Command *newCommand = nullptr;

	command = isCommand(message);
	if (!command.empty()) {
		newCommand = this->commandList_[command];
		finalMessage = newCommand->execute(message, *this->userVector_[index - 1]);
		send(fd, finalMessage.c_str(), finalMessage.size(), 0);
	} else {
		// std::cout << "Received from user " << (fd - 3) << ": " << message;
		// Dispatch to all user on the current channel of the user
		;
	}
	std::cout << "Received from user " << (fd - 3) << ": " << message;
}

const string Server::isCommand(const std::string &message) const {
	// Need more checkup for each command.
	if (message.empty())
		return ("");
	else if (message.find(NICK) == 0) {
		return (NICK);
	} else if (message.find(PING) == 0) {
		return (PING);
	} else if (message.find(USER) == 0) {
		return (USER);
	} else if (message.find(JOIN) == 0) {
		return (JOIN);
	} else {
		return ("");
	}
}

//////////////////////////////////////////////////////////////////////

const int &Server::getUserCount() const { return userCount_; }

const int &Server::getChannelCount() const { return channelCount_; }

const int &Server::getFd() const { return poll_[0].fd; }

void Server::setUserCount(int count){ userCount_ += count; }

void Server::setChannelCount(int count){ channelCount_ += count; }