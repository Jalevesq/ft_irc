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
	std::map<int, User *>::iterator it = listUser_.begin();
	for (; it != listUser_.end(); ++it)
		delete it->second;
	close(poll_[0].fd); 

	std::map<string, Command *> ::iterator iterator;
	iterator = this->commandList_.begin();
	for (; iterator != this->commandList_.end(); iterator++) {
		delete iterator->second;
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
}

//////////////////////////////////////////////
//	   Main loop that handle everything   	//
//////////////////////////////////////////////

void Server::serverRun()
{
	int userFd;
	char buffer[1024];
	while (true)
	{
		poll(this->poll_.data(), this->userCount_ + 1, 100);
		//	throw std::runtime_error("Poll failure"); // fix later
		if (this->poll_[0].revents & POLLIN)
			acceptUser();
		for (int i = 1; i <= userCount_; i++){
			userFd = this->poll_[i].fd;
			if (this->poll_[i].revents & (POLLHUP | POLLERR | POLLNVAL)){
				cout << "user " << this->listUser_[userFd]->getMessage() << " (fd: " << poll_[i].fd << ") disconnected" << endl;
				disconnectUser(i, userFd);
			}
			else if (poll_[i].revents & POLLIN){
				User &liveUser = *this->listUser_[userFd];
				int ret = recv(poll_[i].fd, buffer, 1024, MSG_DONTWAIT);
				if (ret == -1)
					throw std::runtime_error("Recv failure"); // fix later. Disconnect only the user that has a problem ? disconnectUser(i) ?
				buffer[ret] = '\0';
				handleMessage(buffer, liveUser);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////
//	   Handle each message. Is it a command or a normal message?  	//
//////////////////////////////////////////////////////////////////////

void Server::handleMessage(const std::string &message, User& liveUser) {
	string finalMessage = "";
	string userMessage = "";
	std::vector<string> cmd;

	cout << "User '" << liveUser.getNickname() << "'" << " (fd: " << liveUser.getFdSocket() << ") says: " << message;

	liveUser.appendMessage(message);
    userMessage = liveUser.getMessage();
    string extractedMessage = factory_.checkDelimiter(liveUser);
    if (extractedMessage.empty()) {
        return ;
    }
	// While loop what will iterate though factory vector

	factory_.SplitCommand(extractedMessage);
	cmd = factory_.getVector();
	std::vector<string>::iterator it = cmd.begin();
	for (; it != cmd.end(); ++it){
		Command *cmd = factory_.CreateCommand();
		if (cmd) {
			if (liveUser.getIsRegistered() == false)
				finalMessage = Auth(cmd, liveUser, *it);
			else
				finalMessage = cmd->execute(*this, *it, liveUser);
			send(liveUser.getFdSocket(), finalMessage.c_str(), finalMessage.size(), 0);
		} else {
			// Distribute to all user in channel. Check if is in a channel bc fuck nc
		}
		factory_.popCommand();
	}
}

const string Server::Auth(Command *cmd, User &liveUser, const string &argument){
	string message = "";
	string cmdName = cmd->getName(); 

	if (cmdName == PING) {
		message = cmd->execute(*this, argument, liveUser);
		return (message);
	}

	if (cmdName != NICK && liveUser.getNickname().empty())
		message = "451 PRIVMSG :You are not registered (Step 1/2). Please enter a nickname (/nick <nickname>)\r\n";
	else if (cmdName == NICK)
		message = cmd->execute(*this, argument, liveUser);
	else if (cmdName != USER)
		message = "451 PRIVMSG :You are not registered (Step 2/2). Please enter a Username (USER <user> 0 * :<user>\r\n";
	else if (cmdName == USER)
		message = message = cmd->execute(*this, argument, liveUser);

	return message;
}

///////////////////////////////////////////////////////////////////////
//	   Deleting user because 'Disconnect' signal recieve from fd     //
///////////////////////////////////////////////////////////////////////

void Server::disconnectUser(int index, int fd){
	removeNickname(listUser_[fd]->getNickname());
	this->poll_.erase(poll_.begin() + index);
	delete listUser_[fd];
	listUser_.erase(fd); // double check
	this->userCount_--;
}

//////////////////////////////////////
//	   Accept & Create new User   	//
//////////////////////////////////////

void Server::acceptUser(){
	socklen_t addressLength = sizeof(address_);;
	int newFd = accept(poll_[0].fd, (struct sockaddr *)&address_, &addressLength);
	if (newFd == -1)
		throw std::runtime_error("Accept failure"); // fix later
	std::cout << "New connection accepted, socket fd: " << newFd  << ". User ID: " << (newFd - 3) << std::endl;	
	createUser(newFd);
}

void Server::createUser(int& newFd){
	struct pollfd newPoll;
	newPoll.fd = newFd;
	newPoll.events = POLLIN;
	newPoll.revents = 0;
	this->poll_.push_back(newPoll);

	User *newUser = new User("", "", newFd);
	this->listUser_[newFd] = newUser;
	userCount_++;
	// this->userVector_.push_back(newUser);

	string newUserMessage;
	newUserMessage = "451 PRIVMSG :You are not registered. Please give a nickname (/nick <nickname>) THEN a Username (USER <user> 0 * :<user>)\r\n";
	send(newFd, newUserMessage.c_str(), newUserMessage.size(), 0);
	// this->listUser_.push_back(newUser);
}

//////////////////////////////////////////////////////////////////////

void Server::addNickname(const string& nickname) {
    this->nicknameList_.insert(nickname);
}
bool Server::checkNickname(const string &nickname) const {
	if (this->nicknameList_.find(nickname) != this->nicknameList_.end())
		return (true);
    return (false);
}
void Server::removeNickname(const string& nickname) {
    std::set<std::string>::iterator it = this->nicknameList_.find(nickname);
    if (it != this->nicknameList_.end()) {
        this->nicknameList_.erase(it);
    }
}

const int &Server::getUserCount() const { return userCount_; }

const int &Server::getChannelCount() const { return channelCount_; }

const int &Server::getFd() const { return poll_[0].fd; }

void Server::setUserCount(int count){ userCount_ += count; }

void Server::setChannelCount(int count){ channelCount_ += count; }