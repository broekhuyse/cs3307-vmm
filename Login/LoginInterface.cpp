#include <iostream>
#include "LoginInterface.h"

using namespace std;

LoginInterface::LoginInterface()
{
}

LoginInterface::LoginInterface(Login login)
{
    this->login = login;
}

void LoginInterface::createAccountPrompt()
{
    int result = -1;
    while (result < 0)
    {
        string username, password;
        
        cout << "Username: " << endl;
        getline(cin, username);

        cout << "Password: " << endl;
        getline(cin, password);

        result = login.createAccount(username, password);
        if (result == -1)
        {
            cout << "Username already exists, please try again." << endl;
        }
        else
        {
            cout << "Account created." << endl;
        }
    }
}

void LoginInterface::loginPrompt()
{
    int result = -1;
    string username, password;
    while (result < 0)
    {
        if (result != -2)
        {
            // do not prompt for username again if only the password does not match
            cout << "Username: " << endl;
            getline(cin, username);
        }

        cout << "Password: " << endl;
        getline(cin, password);

        result = login.checkLogin(username, password);
        if (result == -1)
        {
            cout << "Username does not exist, please try again." << endl;
        }
        else if (result == -2)
        {
            cout << "Password does not match, please try again." << endl;
        }
        else
        {
            cout << "Logging in..." << endl;
        }
    }
}