#include "../include/Mode.hpp"
#include "../include/Server.hpp"
#include "../include/Utility.hpp"
#include "../include/Channel.hpp"
#include <cstdlib>

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

//:BOZO5 472 hey a :is unknown mode char to me for #a
//:user 472 user e :is unkonwn mode char to me for #a


//:irc.localhost 349 hey #a :End of Channel Exception List
/*ERR_UMODEUNKNOWNFLAG (501)

  "<client> :Unknown MODE flag"

Indicates that a MODE command affecting a user contained a MODE letter that was not recognized. The text used in the last param of this message may vary.*/
//+li or -
typedef std::vector<string>::iterator iterator;

/*
 *****************************************************************************
 **                                 +                                       **
 *****************************************************************************
*/

void Mode::parseModePlus(iterator &it, iterator &end, User &liveUser, Channel *channel){
	string parameter = *it;
	if (parameter.size() == 1){
		sendUserError("461 MODE+ :Not enough parameters\r\n", liveUser.getFdSocket());
		return;
	}
	for (int i = 1; parameter[i]; i++){
		if (parameter[i] == 'i')
			setNoArgument(liveUser, channel, MODE_INVITE_ONLY);
		else if (parameter[i] == 't')
			setNoArgument(liveUser, channel, MODE_TOPIC_RESTRICTED);
		else if (parameter[i] == 'k')
			parseKeyMode(it, end, liveUser, channel);
		else if (parameter[i] == 'o')
			parseModeOp(it, end, liveUser, channel);
		else if (parameter[i] == 'l')
			parseModeLimit(it, end, liveUser, channel);
		else
			sendInvalidToken(channel->getChannelName(), liveUser, parameter[i]);
	}
}

void Mode::parseKeyMode(iterator &it, iterator &end, User &liveUser, Channel *channel){
	std::string message;
	it++;
	if (it == end){
		sendUserError("696 " + channel->getChannelName() + " k + :No key were provided\r\n", liveUser.getFdSocket());
		return;
	}
	channel->setPassword(*it);
	channel->setMode(MODE_CHANNEL_KEY);
	message = ":" + liveUser.getNickname() + " MODE " + channel->getChannelName() + " The channel is now password protected\r\n";
	channel->broadCastAll(message);
}

void Mode::parseModeOp(iterator &it, iterator &end, User &liveUser, Channel *channel){
	std::string message;
	it++;
	if (it == end){
		sendUserError("696 " + channel->getChannelName() + " + :No user were provided\r\n", liveUser.getFdSocket());
		return;
	}
	if (!channel->isUserInChannel(*it)){
		sendUserError("401 " + *it + " :No such nickname\r\n", liveUser.getFdSocket());
		return;
	}
	channel->setMode(MODE_CHANNEL_OPERATOR);
	channel->setUserOperator(channel->getUser(*it), true);
	message = ":" + liveUser.getNickname() + " MODE " + channel->getChannelName() + " " + *it + " has been promoted to operator\r\n";
	channel->broadCastAll(message);
	channel->broadCastUserList();
}

void Mode::parseModeLimit(iterator &it, iterator &end, User &liveUser, Channel *channel){
	std::string message;
	it++;
	if (it == end){
		sendUserError("696 " + channel->getChannelName() + " + l :No number were provided\r\n", liveUser.getFdSocket());
		return;
	}
	std::string number = *it;
	for (int i = 0; number[i]; i++){
		if (number[i] < '0' || number[i] > '9'){
			sendUserError("400 +l argument provided wasn't a digit\r\n", liveUser.getFdSocket());
			return;
		}
	}
	long int amount = strtol(number.c_str(), NULL, 10);
	if (amount > 50 && amount >= 1){
		sendUserError("400 +l user limit argument was over 50\r\n", liveUser.getFdSocket());
		return;//fix later no key provided not sending to right channel
	}
	channel->setUserLimit(amount);
	channel->setMode(MODE_USER_LIMIT);
	message = ":" + liveUser.getNickname() + " MODE " + channel->getChannelName() + " The channel now has a limit of " + number + " of users\r\n";
	channel->broadCastAll(message);
}

void Mode::setNoArgument(User &user, Channel *channel, const unsigned char &flag){
	std::string message;
	if (flag == MODE_INVITE_ONLY){
		channel->setMode(MODE_INVITE_ONLY);
		message = ":" + user.getNickname() + " MODE " + channel->getChannelName() + " The channel is invite only now +(i)\r\n";
	}
	else{
		channel->setMode(MODE_TOPIC_RESTRICTED);
		message = ":" + user.getNickname() + " MODE " + channel->getChannelName() + " The topic can now only be changed by operator +(t)\r\n";
	}
	channel->broadCastAll(message);
}

/*
 *****************************************************************************
 **                            negative                                     **
 *****************************************************************************
*/

void Mode::parseModeNegatif(iterator &it, iterator &end, User &liveUser, Channel *channel){
	std::string code = *it;
	(void)it;
	(void)end;
	(void)liveUser;
	(void)channel;
}

/*
 *****************************************************************************
 **                            utility                                      **
 *****************************************************************************
*/

void Mode::sendUserError(const string &message, int fd){
	send(fd, message.c_str(), message.size(), 0);
}

void Mode::sendInvalidToken(const string channelName, User &liveUser, const char c){
	std::string message = ":" + liveUser.getNickname() + " 472 " + c + " " + channelName + " :is unkonwn mode char to me for " + channelName + "\r\n";
	send(liveUser.getFdSocket(), message.c_str(), message.size(), 0);
}


const string Mode::parseMode(Channel *channel, std::vector<string> &tokens, User &liveUser){
	std::vector<string>::iterator it = tokens.begin();
	std::vector<string>::iterator end = tokens.end();
	do{
		std::string token = *it;
		if (token[0] == '+')
			parseModePlus(it, end, liveUser, channel);
		else if (token[0] == '-')
			parseModeNegatif(it, end, liveUser, channel);
		if (it == tokens.end())
			return ""; //fix return invalid token or something ~~~
		it++;
	} 
	while(it != tokens.end());
	return "";
}

string Mode::execute(Server &server, const string& message, User& liveUser){
	std::vector<string> tokens = tokenize(message, " ");
	if (tokens.size() == 1)
		return "461 " + liveUser.getNickname() + " MODE :Not enough parameters\r\n";
	if (!server.doesChannelExist(tokens[1]))
		return "403 " + liveUser.getNickname() + " " + tokens[1] + " :No such channel\r\n";
	Channel *channel = server.getChannel(tokens[1]);
	if (tokens.size() == 2){
		channel->sendCurrentMode(&liveUser);
		return "";
	}
	if (channel->isOperator(&liveUser) == false)
		return ":" + liveUser.getNickname() + " 482 " + liveUser.getNickname() + " " + tokens[1] + " :You're not channel operator\r\n";
	return parseMode(channel, tokens, liveUser);
}