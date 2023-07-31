#include "../include/Utility.hpp"

bool isNotEmptyString(const std::string &string){
	for (int index = 0; string[index]; index++){
		if (string[index] != ' ' && string[index] != '\0')
			return true;
	}
	return false;
}

// void tokenize(const string &message){
// 	std::vector<std::string> vector_;
// 	std::string token;
// 	size_t index = 0;
// 	size_t end = message.find(" ");

// 	while (end != std::string::npos){
// 		token = message.substr(index, end - index);
// 		if (isNotEmptyString(token) && token.find(" ") == std::string::npos)
// 			tokens_.push_back(token);
// 		index = end + 1;
// 		end = message.find(" ", index);
// 	}
// 	token = message.substr(index);
// 	if (isNotEmptyString(token) && token.find(" ") == std::string::npos)
// 		tokens_.push_back(token);
// }

// const std::string Join::createChannel(Server &server, User &liveUser) const{
// 	Channel *channel = new Channel(tokens_[1], server.getUserPointer(liveUser.getFdSocket()));
// 	server.addChannel(tokens_[1], channel);
// 	return ":" + liveUser.getNickname() + " " + tokens_[0] + " " + tokens_[1] + "\r\n";
// }