#include "../include/Mode.hpp"
#include "../include/Server.hpp"
#include "../include/Utility.hpp"
#include "../include/Channel.hpp"
#include <cstdlib>

Mode::Mode() {}
Mode::~Mode() {}	

typedef std::vector<string>::iterator iterator_;

/*
 *****************************************************************************
 **                                 +                                       **
 *****************************************************************************
*/

void Mode::parseModePlus(iterator_ &it, iterator_ &end, User &liveUser, Channel *channel, int &index, string &token){
	index++;
	if (token.size() == 1){
		sendUserError("461 MODE :Not enough parameters\r\n", liveUser.getFdSocket());
		return;
	}
	for (; token[index]; index++){
		if (token[index] == 'i')
			setNoArgument(liveUser, channel, MODE_INVITE_ONLY);
		else if (token[index] == 't')
			setNoArgument(liveUser, channel, MODE_TOPIC_RESTRICTED);	
		else if (token[index] == 'k')
			parseKeyMode(it, end, liveUser, channel);
		else if (token[index] == 'o')
			parseModeOp(it, end, liveUser, channel);
		else if (token[index] == 'l')
			parseModeLimit(it, end, liveUser, channel);
		else if (token[index] == '-' && token[index + 1] != '-' && token[index + 1] != '+')
			return;
		else if (token[index] == '+' && token[index + 1] != '-' && token[index + 1] != '+')
			continue;
		else
			sendInvalidToken(channel->getChannelName(), liveUser, token[index]);
	}
}

void Mode::parseKeyMode(iterator_ &it, iterator_ &end, User &liveUser, Channel *channel){
	std::string message;
	if (it == end){
		sendUserError("696 " + channel->getChannelName() + " k + :No key were provided\r\n", liveUser.getFdSocket());
		return;
	}
	std::string password = *it;
	if (password.find("+-", 0) != string::npos){
		sendUserError("400 Password contain +-\r\n", liveUser.getFdSocket());
	}
	channel->setPassword(*it);
	channel->setMode(MODE_CHANNEL_KEY);
	message = ":" + liveUser.getNickname() + " MODE " + channel->getChannelName() + " +k\r\n";
	channel->broadCastAll(message);
	it++;
}

void Mode::parseModeOp(iterator_ &it, iterator_ &end, User &liveUser, Channel *channel){
	std::string message;
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
	message = ":" + liveUser.getNickname() + " MODE " + channel->getChannelName() + " +o\r\n";
	channel->broadCastAll(message);
	channel->broadCastUserList();
	it++;
}

void Mode::parseModeLimit(iterator_ &it, iterator_ &end, User &liveUser, Channel *channel){
	std::string message;
	if (it == end){
		sendUserError("696 " + channel->getChannelName() + " + l :No number were provided\r\n", liveUser.getFdSocket());
		return;
	}
	std::string number = *it;
	for (int i = 0; number[i]; i++){
		if (number[i] < '0' || number[i] > '9'){
			sendUserError("696 " + channel->getChannelName() + " +l :Argument wasn't a digit\r\n", liveUser.getFdSocket());
			return;
		}
	}
	long int amount = strtol(number.c_str(), NULL, 10);
	if (amount > 50 || amount < 1){
		sendUserError("400 +l user limit argument was over " + std::to_string(MAX_USER) + "\r\n", liveUser.getFdSocket());
		return;//fix later no key provided not sending to right channel
	}
	channel->setUserLimit(amount);
	channel->setMode(MODE_USER_LIMIT);
	message = ":" + liveUser.getNickname() + " MODE " + channel->getChannelName() + " +l\r\n";
	channel->broadCastAll(message);
	it++;
}

void Mode::setNoArgument(User &user, Channel *channel, const unsigned char &flag){
	std::string message;
	if (flag == MODE_INVITE_ONLY){
		if (channel->isModeFlagSet(MODE_INVITE_ONLY)){
			message = ": 400 " + user.getNickname() + " channel " + channel->getChannelName() + " +i :Mode is already set\r\n";
			sendUserError(message, user.getFdSocket());
			return;
		}
		channel->setMode(MODE_INVITE_ONLY);
		channel->clearUserInInviteList();
		message = ":" + user.getNickname() + " MODE " + channel->getChannelName() + " +i\r\n";
	}
	else{
		if (channel->isModeFlagSet(MODE_TOPIC_RESTRICTED)){
			message = ": 400 " + user.getNickname() + " channel " + channel->getChannelName() + " +t :Mode is already set\r\n";
			sendUserError(message, user.getFdSocket());
			return;
		}
		channel->setMode(MODE_TOPIC_RESTRICTED);
		message = ":" + user.getNickname() + " MODE " + channel->getChannelName() + " +t\r\n";
	}
	channel->broadCastAll(message);
}

/*
 *****************************************************************************
 **                            negative                                     **
 *****************************************************************************
*/

void Mode::parseModeNegatif(iterator_ &it, iterator_ &end, User &liveUser, Channel *channel, int &index, string &token){
	index++;
	string parameter = token;
	if (parameter.size() == 1){
		sendUserError("461 MODE+ :Not enough parameters\r\n", liveUser.getFdSocket());
		return;
	}
	for (; parameter[index]; index++){
		if (parameter[index] == 'i')
			setNoArgumentNegative(liveUser, channel, MODE_INVITE_ONLY);
		else if (parameter[index] == 't')
			setNoArgumentNegative(liveUser, channel, MODE_TOPIC_RESTRICTED);
		else if (parameter[index] == 'k')
			setNoArgumentNegative(liveUser, channel, MODE_CHANNEL_KEY);
		else if (parameter[index] == 'o')
			parseNegativeOP(it, end, liveUser, channel);
		else if (parameter[index] == 'l')
			setNoArgumentNegative(liveUser, channel, MODE_USER_LIMIT);
		else if (parameter[index] == '+' && parameter[index + 1] != '-' && parameter[index + 1] != '+')
			return;
		else if (parameter[index] == '-' && parameter[index + 1] != '-' && parameter[index + 1] != '+')
			continue;
		else
			sendInvalidToken(channel->getChannelName(), liveUser, parameter[index]);
	}
}

void Mode::sendUnsetError(const std::string &mode, Channel *channel, User &user){
	std::string errorMessage;
	errorMessage = ": 400 " + user.getNickname() + " Channel " + channel->getChannelName() 
		+ " " + mode + " :Mode is already not set\r\n";
	sendUserError(errorMessage, user.getFdSocket());
}

void Mode::setNoArgumentNegative(User &user, Channel *channel, const unsigned char &flag){
	std::string message;
	if (flag == MODE_INVITE_ONLY){
		if (channel->isModeFlagSet(MODE_INVITE_ONLY) == false)
			return sendUnsetError("-i", channel, user);
		message = ":" + user.getNickname() + " MODE " + channel->getChannelName() + " -i\r\n";
	}
	else if (flag == MODE_TOPIC_RESTRICTED){
		if (channel->isModeFlagSet(MODE_TOPIC_RESTRICTED) == false)
			return sendUnsetError("-t", channel, user);
		message = ":" + user.getNickname() + " MODE " + channel->getChannelName() + " -t\r\n";
	}
	else if (flag == MODE_CHANNEL_KEY){
		if (channel->isModeFlagSet(MODE_CHANNEL_KEY) == false)
			return sendUnsetError("-k", channel, user);
		message = ":" + user.getNickname() + " MODE " + channel->getChannelName() + " -k\r\n";
	}
	else if (flag == MODE_USER_LIMIT){
		if (channel->isModeFlagSet(MODE_USER_LIMIT) == false)
			return sendUnsetError("-l", channel, user);
		message = ":" + user.getNickname() + " MODE " + channel->getChannelName() + " -l\r\n";
	}
	channel->unsetMode(flag);
	channel->broadCastAll(message);
}

void Mode::parseNegativeOP(iterator_ &it, iterator_ &end, User &liveUser, Channel *channel){
	if (it == end){
		sendUserError("696 " + channel->getChannelName() + " -o :No user were provided\r\n", liveUser.getFdSocket());
		return;
	}
	if (liveUser.getOperator() == false){
		sendUserError("481 :Permission Denied, you don't have the right\r\n", liveUser.getFdSocket());
		return;
	}
	std::string user = *it;
	if (channel->isUserInChannel(user) == false){
		sendUserError("401 " + *it + " :No such nickname\r\n", liveUser.getFdSocket());
		return;
	}
	channel->setUserOperator(channel->getUser(user), false);
	std::string message = ":" + liveUser.getNickname() + " MODE " + channel->getChannelName() + " -o\r\n";
	channel->broadCastAll(message);
	channel->broadCastUserList();
	++it;
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
	std::string message = ":" + liveUser.getNickname() + " 472 " + c + " " + channelName + " :is unknown mode char to me for " + channelName + "\r\n";
	send(liveUser.getFdSocket(), message.c_str(), message.size(), 0);
}

const string Mode::parseMode(Channel *channel, std::vector<string> &tokens, User &liveUser)
{
	std::vector<string>::iterator it = tokens.begin();
	std::vector<string>::iterator end = tokens.end();
	it += 2;
	do
	{
		std::string token = *it;
		it++;
		if (token[0] != '+' && token[0] != '-')
			return "696 " + channel->getChannelName() + " MODE :Invalid parameter\r\n";
		int index = 0;
		while (token[index])
		{
			if (token[index] == '+')
				parseModePlus(it, end, liveUser, channel, index, token);
			else if (token[index] == '-')
				parseModeNegatif(it, end, liveUser, channel, index, token);
		}
	} while (it != tokens.end());
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
	if (channel->isUserInChannel(liveUser.getNickname()) == false)
		return ":" + liveUser.getNickname() + " 442 " + channel->getChannelName() + " :You're not on that channel\r\n";
	if (channel->isOperator(&liveUser) == false)
		return ":" + liveUser.getNickname() + " 482 " + liveUser.getNickname() + " " + tokens[1] + " :You're not channel operator\r\n";
	return parseMode(channel, tokens, liveUser);
}