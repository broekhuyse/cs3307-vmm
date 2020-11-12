#ifndef LOGIN_COLLECTION_H
#define LOGIN_COLLECTION_H

#include <unordered_map>
#include <string>
#include "Member.h"

class LoginCollection
{
private:
    std::unordered_map<std::string, std::pair<std::string, Member>> loginCollection;
    int currentHighestMemberID;

public:
    LoginCollection();
    ~LoginCollection();
    int addMember(std::string username, std::string password, std::string fname, std::string lname, bool isAdmin, std::string membershipType);
    Member *findMember(std::string username, std::string password);

    int deleteUser(std::string username, std::string password);
    int changePassword(std::string username, std::string oldPassword, std::string newPassword);
	std::unordered_map<std::string, std::pair<std::string, Member>> getMap();
	void setCollection(std::unordered_map<std::string, std::pair<std::string, Member>>,int highestID);
};

#endif