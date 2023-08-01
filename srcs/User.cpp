#include "../include/User.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

User::User(string newNickname, string newUsername, int newFdSocket) : nickname_(newNickname), username_(newUsername) {
	this->operator_ = false;
	this->fdSocket_= newFdSocket;
	this->isRegistered_[PASS] = false;
	this->isRegistered_[AUTH] = false;
}

User::User() : nickname_("user"), username_("user"), operator_(false), fdSocket_(-1) {}

// User::User( const User & src )
// {
// }


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

User::~User()
{
	close(this->fdSocket_);
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

// User &				User::operator=( User const & rhs )
// {
// 	//if ( this != &rhs )
// 	//{
// 		//this->_value = rhs.getValue();
// 	//}
// 	return *this;
// }

// std::ostream &			operator<<( std::ostream & o, User const & i )
// {
// 	//o << "Value = " << i.getValue();
// 	return o;
// }


/*
** --------------------------------- METHODS ----------------------------------
*/


void User::clearMessage() {
	this->message_ = "";
}

void User::appendMessage(const string& appendMessage) {
	string newMessage = "";
	// rm \n if there is no \r before
	for (unsigned long int i = 0; i < appendMessage.size(); i++) {
		if (appendMessage[i] != '\n' || (appendMessage[i] == '\n'
			&& ( i - 1 <= appendMessage.size() && appendMessage[i - 1] == '\r')))
			newMessage += appendMessage[i];
	}
	this->message_.append(newMessage);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/
const string& User::getNickname() const {
	return (this->nickname_);
}

const string& User::getUsername() const {
	return (this->username_);
}

const int& User::getFdSocket() const {
	return (this->fdSocket_);
}

const bool& User::getOperator() const {
	return (this->operator_);
}

const string& User::getMessage() const {
	return (this->message_);
}

const bool& User::getIsPass() const {
	return (this->isRegistered_[PASS]);
}

const bool& User::getIsRegister() const {
	return (this->isRegistered_[AUTH]);
}

void User::setIsPass(const bool &setPass) {
	this->isRegistered_[PASS] = setPass;
}

void User::setIsRegister(const bool &setRegister) {
	this->isRegistered_[AUTH] = setRegister;
}

void User::setNickname(const string &newNickname) {
	this->nickname_ = newNickname;
}

void User::setUsername(const string &newUsername) {
	this->username_ = newUsername;
}

void User::setOperator(const bool &newOperator) {
	this->operator_ = newOperator;
}

void User::setfdSocket(const int &fd) {
	this->fdSocket_ = fd;
}

/* ************************************************************************** */

void User::addChannelUser(const string &name){
	channels_.insert(name);
}

void User::removeChannelUser(const string &name){
	channels_.erase(name);
}

std::set<string> User::getChannelSet() { return channels_;}

/* ************************************************************************** */