#include "../include/Utility.hpp"

bool isNotEmptyString(const std::string &string){
	for (int index = 0; string[index]; index++){
		if (string[index] != ' ' && string[index] != '\0')
			return true;
	}
	return false;
}

std::vector<std::string> tokenize(const std::string &message){
	std::vector<std::string> vector_;
	std::string token;
	size_t index = 0;
	size_t end = message.find(" ");

	while (end != std::string::npos){
		token = message.substr(index, end - index);
		if (isNotEmptyString(token) && token.find(" ") == std::string::npos)
			vector_.push_back(token);
		index = end + 1;
		end = message.find(" ", index);
	}
	token = message.substr(index);
	if (isNotEmptyString(token) && token.find(" ") == std::string::npos)
		vector_.push_back(token);
	return vector_;
}