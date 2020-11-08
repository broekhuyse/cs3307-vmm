
#include "LoginCollection.h"
#include <iostream>
#include <string>

LoginCollection::LoginCollection()
{
    currentHighestMemberID = 0;
}

/*
* Name: addMember
* Description: Adds a user to the collection of logins with their username and password
* Params: username: username of the new user
*         password: password of the new user (encoded)
*         fname: first name of new user
*         lname: last name of new user
*         isAdmin: admin status of new user
*         membershipType: membership type of new user
* Return: 0 on success, -1 on failure (username already exists), -2 if password is not secure enough
*/
int LoginCollection::addMember(std::string username, std::string password, std::string fname, std::string lname, bool isAdmin, std::string membershipType)
{
    if (loginCollection.find(username) != loginCollection.end())
    {
        // username already exists
        return -1;
    }

    // check if password is secure enough
    bool digit, upper, lower, special;
    digit = upper = lower = special = false;
    int length = password.length();
    if (length < 8)
    {
        return -2;
    }
    for (int i = 0; i < length; i++)
    {
        if (islower(password[i]))
        {
            lower = true;
        }
        else if (isupper(password[i]))
        {
            upper = true;
        }

        if (isdigit(password[i]))
        {
            digit = true;
        }
        if (!isalpha(password[i]) && !isdigit(password[i]))
        {
            special = true;
        }
    }
    if (!lower || !upper || !digit || !special)
    {
        return -2;
    }

    // check if name is correct formatting

    //alternate way to insert
    auto test = std::make_pair(password, Member(fname, lname, isAdmin, currentHighestMemberID += 1, membershipType, 0.0));
    auto insert = std::make_pair(username, test);
    this->loginCollection.insert(insert);

    return 0;

    // add user to the collection
    /*
   loginCollection[username].first = password;
   loginCollection[username].second = Member(fname, lname, isAdmin, currentHighestMemberID += 1, membershipType);
    return 0;
	*/
}

/*
* Name: findMember
* Description: Adds a user to the collection of logins with their username and password
* Params: username: username of the user
*         password: password of the user (encoded)
* Return: NULL if username doesnt exist or password does not match
*         Member* if the member exists
*/
Member *LoginCollection::findMember(std::string username, std::string password)
{
    std::unordered_map<std::string, std::pair<std::string, Member>>::iterator search = loginCollection.find(username);
    if (search == loginCollection.end() || search->second.first != password)
    {
        // username does not exist in the system or password does not match

        // debugging to see if password mismatch or usename not in collection
        // std::cout << "Found password: " << (search->second.first)  << " Input password: " << password << std::endl;
        // std::cout << (search == loginCollection.end()) << (search->second.first != password);
        return NULL;
    }
    else
    {
        // username and password match entry
        return &search->second.second;
    }
}

/*
* Name: deleteUser
* Description: Changes the password of an existing user in the database
* Params: username: username of the user to be deleted
*         password: password of the user to be deleted(encoded)
* Return: 0 on success, -1 if username doesnt exist or password does not match
*/
int LoginCollection::deleteUser(std::string username, std::string password)
{
    const Member *membercheck = findMember(username, password);
    if (membercheck == NULL)
    {
        return -1;
    }
    else
    {
        // Member exists and password is correct
        loginCollection.erase(username);
        return 0;
    }
}

/*
* Name: changePassword
* Description: Changes the password of an existing user in the database
* Params: username: username of the user
*         oldPassword: oldPassword of the user (encoded)
*         newPassword: newPassword of the user (encoded)
* Return: 0 on success, -1 if username does not exist or if oldPassword is incorrect for username
*/
int LoginCollection::changePassword(std::string username, std::string oldPassword, std::string newPassword)
{
    const Member *membercheck = findMember(username, oldPassword);
    if (membercheck == NULL)
    {
        return -1;
    }
    else
    {
        // Member exists and password is correct
        loginCollection[username].first = newPassword;
        return 0;
    }
}

std::unordered_map<std::string, std::pair<std::string, Member>> LoginCollection::getMap()
{

    return this->loginCollection;
}
void LoginCollection::setCollection(std::unordered_map<std::string, std::pair<std::string, Member>> map)
{
    loginCollection = map;
}
