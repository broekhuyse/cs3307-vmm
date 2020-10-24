// Could potentially merge into login, but made a different class currently to separate GUI from the act of logging in, in the future

#ifndef LOGIN_INTERFACE_H
#define LOGIN_INTERFACE_H

#include <string>
#include "Login.h"

class LoginInterface
{
private:
    Login login;

public:
    LoginInterface();
    LoginInterface(Login login);
    void createAccountPrompt();
    void loginPrompt();
};

#endif