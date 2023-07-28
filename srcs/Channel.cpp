#include "../include/Channel.hpp"
#include "../include/User.hpp"

Channel::Channel(const std::string &name, const User *user) {
	(void)user;
	(void)name;
}

Channel::~Channel() {}