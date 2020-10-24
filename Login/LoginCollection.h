#ifndef LOGIN_COLLECTION_H
#define LOGIN_COLLECTION_H

#include <unordered_map>
#include <string>

class LoginCollection
{
private:
    std::unordered_map<std::string, std::string> loginCollection;

public:
    LoginCollection();
    int addUser(std::string username, std::string password);
    int findUser(std::string username, std::string password);

    int deleteUser(std::string username, std::string password);
    int changePassword(std::string username, std::string oldPassword, std::string newPassword);
};

#endif