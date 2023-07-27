#include "../include/User.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

User::User(string newNickname, string newUsername, int newFdSocket) : nickname_(newNickname), username_(newUsername) {
	this->operator_ = false;
	this->fdSocket_= newFdSocket;
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
	this->message_.append(appendMessage);
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