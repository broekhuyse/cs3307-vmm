#include "Login.h"

Login::Login()
{
}

/*
* Name: Login
* Description: Constructor for Login class to set the LoginCollection
* Params: loginCollection: The collection used to store the username and password data
* Return: none
*/
Login::Login(LoginCollection loginCollection)
{
    this->loginCollection = loginCollection;
}

/*
* Name: createAccount
* Description: Adds a user to the collection of logins with their username and password
* Params: username: username of the new user
*         password: password of the new user (to be encoded)
* Return: 0 on success, -1 on failure (username already exists)
*/
int Login::createAccount(std::string username, std::string password)
{
    // Directly add user to login collection (update to encrypt password)
    return loginCollection.addUser(username, password);
}

/*
* Name: checkLogin
* Description: Adds a user to the collection of logins with their username and password
* Params: username: username of the new user
*         password: password of the new user (to be encoded)
* Return: 0 on success, -1 on failure (username already exists)
*/
int Login::checkLogin(std::string username, std::string password)
{
    // Directly add user to login collection (update to encrypt password)
    return loginCollection.findUser(username, password);
}

void Login::setLoginCollection(LoginCollection collection)
{
    loginCollection = collection;
}
