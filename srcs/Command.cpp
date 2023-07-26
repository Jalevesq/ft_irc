#include "../include/Command.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Command::Command()
{
    this->commandName_ = "<None>";
}

// Command::Command( const Command & src )
// {
// }


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Command::~Command()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

// Command &				Command::operator=( Command const & rhs )
// {
// 	//if ( this != &rhs )
// 	//{
// 		//this->_value = rhs.getValue();
// 	//}
// 	return *this;
// }

/*
** --------------------------------- METHODS ----------------------------------
*/


/*
** --------------------------------- ACCESSOR ---------------------------------
*/

const string& Command::getName() {
    return (this->commandName_);
}



/* ************************************************************************** */