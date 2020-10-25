#include <iostream>
#include "LoginInterface.h"
#include "Member.h"

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
        string username, password, fname, lname;
        
        cout << "Username: " << endl;
        getline(cin, username);

        cout << "Password (must be longer than 8 characters and contain uppercase, lowercase, and a special symbol): " << endl;
        getline(cin, password);

        cout << "First name: " << endl;
        getline(cin, fname);

        cout << "Last name: " << endl;
        getline(cin, lname);

        result = login.createAccount(username, password, fname, lname, false, "temp");
        if (result == -1)
        {
            cout << "Username already exists, please try again." << endl;
        }
        else if (result == -2){
            cout << "Password is not secure enough, please try again." << endl;
        }
        else
        {
            cout << "Account created." << endl;
        }
    }
}

void LoginInterface::loginPrompt()
{
    const Member *result = NULL;
    string username, password;
    while (result == NULL)
    {
        cout << "Username: " << endl;
        getline(cin, username);

        cout << "Password: " << endl;
        getline(cin, password);

        result = login.checkLogin(username, password);
        if (result == NULL)
        {
            cout << "Username does not exist or password does not match, please try again." << endl;
        }
        else
        {
            // Set current user in system to the resulting member
            cout << "Logging in..." << endl;
        }
    }

    // Temp debugging print for member information
    cout << "ID: " << result->getID() << endl;
    cout << "Name: " << result->getName().first << " " << result->getName().second << endl;
    cout << "Currency: " << result->getCurrency() << endl;
}