
#include "LoginCollection.h"

LoginCollection::LoginCollection()
{
}

/*
* Name: addUser
* Description: Adds a user to the collection of logins with their username and password
* Params: username: username of the new user
*         password: password of the new user (encoded)
* Return: 0 on success, -1 on failure (username already exists)
*/
int LoginCollection::addUser(std::string username, std::string password)
{
    if (loginCollection.find(username) != loginCollection.end())
    {
        // username already exists
        return -1;
    }
    // add user to the collection
    loginCollection[username] = password;
    return 0;
}

/*
* Name: findUser
* Description: Adds a user to the collection of logins with their username and password
* Params: username: username of the user
*         password: password of the user (encoded)
* Return: 0 on success, -1 if username doesnt exist, -2 if password does not match
* ################### MAYBE CHANGE TO RETURN THE MEMBER AND HAVE THE COLLECTION STORE THE MEMBER INSTEAD OF JUST LOGIN INFO (WHERE IS MEMBER INFO BEING SAVED CURRENTLY?)
*/
int LoginCollection::findUser(std::string username, std::string password)
{
    std::unordered_map<std::string, std::string>::const_iterator search = loginCollection.find(username);
    if (search == loginCollection.end())
    {
        // username does not exist in the system
        return -1;
    }
    else if (search->second != password)
    {
        // password does not match
        return -2;
    }
    else
    {
        // username and password match entry
        return 0;
    }
}

/*
* Name: deleteUser
* Description: Changes the password of an existing user in the database
* Params: username: username of the user to be deleted
*         password: password of the user to be deleted(encoded)
* Return: 0 on success, -1 if username doesnt exist, -2 if password does not match (same as finduser)
*/
int LoginCollection::deleteUser(std::string username, std::string password)
{
    int result = findUser(username, password);

    if(result == 0){
        // username and password match
        loginCollection.erase(username);
    }
    return result;
}

/*
* Name: changePassword
* Description: Changes the password of an existing user in the database
* Params: username: username of the user
*         oldPassword: oldPassword of the user (encoded)
*         newPassword: newPassword of the user (encoded)
* Return: 0 on success, -1 if username does not exist, -2 if oldPassword is incorrect for username
*/
int LoginCollection::changePassword(std::string username, std::string oldPassword, std::string newPassword)
{
    std::unordered_map<std::string, std::string>::const_iterator search = loginCollection.find(username);
    if (search == loginCollection.end())
    {
        // username does not exist in the system 
        return -1;
    }
    else if (search->second != oldPassword)
    {
        // password does not match
        return -2;
    }
    else
    {
        // username and password match entry
        loginCollection[username] = newPassword;
        return 0;
    }
}