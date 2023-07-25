#include "../include/User.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

User::User(string newNickname, string newUsername, int newFdSocket) : nickname_(newNickname), username_(newUsername) {
	this->operator_ = false;
	this->fdSocket_= newFdSocket;
}

User::User()
{
}

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

void User::setNickname(string newNickname) {
	this->nickname_ = newNickname;
}

void User::setUsername(string newUsername) {
	this->username_ = newUsername;
}

void User::setOperator(bool newOperator) {
	this->operator_ = newOperator;
}

/* ************************************************************************** */