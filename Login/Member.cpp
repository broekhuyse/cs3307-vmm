#include "Member.h"

using namespace std;

Member::Member()
{
}

/*
* Name: Member
* Description: Constructor for Member class to set the data
* Params: name: Name of the new member
*         isAdmin: Admin status of the member
*         memberID: ID of the member
*         membershipType: membership type of the new member
* Return: none
*/
Member::Member(std::string fname, std::string lname, bool isAdmin, int memberID, std::string membershipType)
{
    this->fname = fname;
    this->lname = lname;
    this->isAdmin = isAdmin;
    this->memberID = memberID;
    this->membershipType = membershipType;
    currency = 0;
}

std::pair<std::string, std::string> Member::getName() const
{
    return std::pair<std::string, std::string>(fname, lname);
}

int Member::getID() const
{
    return memberID;
}

float Member::getCurrency() const
{
    return currency;
}