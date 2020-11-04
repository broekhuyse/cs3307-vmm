#ifndef USERDBCONVERSION_H_
#define USERDBCONVERSION_H_
#include <string>
#include <unordered_map>
#include "Member.h"

class UserDBConversion {

private:

public: 
	UserDBConversion();
	void LoginCollectionToFile(std::unordered_map<std::string, std::pair<std::string, Member>> & map);
	std::unordered_map<std::string, std::pair<std::string, Member>> FileToLoginCollection();

};
#endif