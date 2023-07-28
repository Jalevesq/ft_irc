#include "../include/Channel.hpp"
#include "../include/User.hpp"

Channel::Channel(const std::string &name, const User *user) : channelName_(""), topic_(""),
	password_(""), hasPassword_(false), mode_(0), userLimit_(0){
	(void)user;
	(void)name;
}

Channel::~Channel() {}