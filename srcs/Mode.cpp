#include "../include/Mode.hpp"
#include "../include/Server.hpp"
#include "../include/Utility.hpp"

Mode::Mode() {}
Mode::~Mode() {}	

/*
i (Invite-only channel):
Mode flag: +i
Description: This mode makes the channel invite-only, meaning only invited users can join the channel.
Parameter: This mode does not require any parameters.
t (Restrict TOPIC command to channel operators):

Mode flag: +t
Description: This mode restricts the TOPIC command, allowing only channel operators to change the channel's topic.
Parameter: This mode does not require any parameters.
k (Channel key - password):

Mode flag: +k
Description: This mode sets a channel key (password) that users need to provide to join the channel.
Parameter: The channel key (password) is required as a parameter for this mode.
o (Channel operator privilege):

Mode flag: +o
Description: This mode gives channel operator privilege to a user, allowing them to moderate the channel.
Parameter: The nickname of the user to be granted operator status is required as a parameter for this mode.
l (User limit to channel):

Mode flag: +l
Description: This mode sets a limit on the number of users who can join the channel.
Parameter: The maximum number of users allowed in the channel is required as a parameter for this mode.
*/


//:irc.localhost 403 hey +a :No such channel
//:irc.localhost 482 hey #a :You're not channel operator
//:irc.localhost 472 hey a :is unknown mode char to me for #a
//:irc.localhost 349 hey #a :End of Channel Exception List
string Mode::execute(Server &server, const string& message, User& liveUser){
	std::vector<string> tokens = tokenize(message, " ");
	if (tokens.size() == 1)
		return "461 " + liveUser.getNickname() + " TOPIC :Not enough parameters\r\n";
	std::string channel = tokens[1];
	if (!server.doesChannelExist(tokens[1]))
		return "403 " + liveUser.getNickname() + " " + tokens[1] + ":No such channel\r\n";
	(void)liveUser;
	(void)message;
	return "";
}