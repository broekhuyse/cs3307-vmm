#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include "LoginCollection.h"

class Login
{
private:
    LoginCollection loginCollection;

public:
    Login();
    Login(LoginCollection loginCollection);
    int createAccount(std::string username, std::string password);
    int checkLogin(std::string username, std::string password);

    void setLoginCollection(LoginCollection collection);
};

#endif
