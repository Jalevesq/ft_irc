#include "../include/Utulity.hpp"

bool isNotEmptyString(const std::string &string){
	for (int index = 0; string[index]; index++){
		if (string[index] != ' ' && string[index] != '\0')
			return true;
	}
	return false;
}