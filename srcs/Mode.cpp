#include "../include/Mode.hpp"
#include "../include/Server.hpp"
#include "../include/Utility.hpp"
#include "../include/Channel.hpp"

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
typedef std::vector<string>::iterator bozo;

void Mode::sendInvalidToken(const string channelName, User &liveUser, const char c){
	std::string message = ":" + liveUser.getNickname() + " 472 " + c + " " + channelName + " :is unkonwn mode char to me for " + channelName + "\r\n";
	send(liveUser.getFdSocket(), message.c_str(), message.size(), 0);
}

const string Mode::parseModePlus(bozo &it, bozo &end, User &liveUser, Channel *channel){
	string parameter = *it;
	cout << "HELLO" << endl;
	if (parameter.size() == 1)
		return "BOZO";
	for (int i = 1; parameter[i]; i++){
		if (parameter[i] == 'i')
			channel->setMode(MODE_INVITE_ONLY, &liveUser, parameter[i]);
		else if (parameter[i] == 't')
			channel->setMode(MODE_TOPIC_RESTRICTED, &liveUser, parameter[i]);
		else
			sendInvalidToken(channel->getChannelName(), liveUser, parameter[i]);
	}
	(void)end;
	(void)liveUser;
	(void)channel;
	return "BOZO";
}

const string Mode::parseModeNegatif(bozo &it, bozo &end, User &liveUser, Channel *channel){
	std::string code = *it;
	(void)it;
	(void)end;
	(void)liveUser;
	(void)channel;
	return "BOZO";
}

const string Mode::parseMode(Channel *channel, std::vector<string> &tokens, User &liveUser){
	std::vector<string>::iterator it = tokens.begin();
	std::vector<string>::iterator end = tokens.end();
	(void)channel;
	for (; it != tokens.end(); ++it){
		std::string token = *it;
		if (token[0] == '+')
			parseModePlus(it, end, liveUser, channel);
		else if (token[0] == '-')
			parseModeNegatif(it, end, liveUser, channel);
	}
	return "";
}

string Mode::execute(Server &server, const string& message, User& liveUser){
	std::vector<string> tokens = tokenize(message, " ");
	if (tokens.size() == 1)
		return "461 " + liveUser.getNickname() + " TOPIC :Not enough parameters\r\n";
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