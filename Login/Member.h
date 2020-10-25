#ifndef MEMBER_H
#define MEMBER_H

#include <string>

class Member
{
private:
    float currency;
    std::string membershipType; // Probably need to change this to something other than string
    std::string fname;
    std::string lname;
    bool isAdmin;
    int memberID;
    //purchasehistory
    //lastlogin

public:
    Member();
    Member(std::string fname, std::string lname, bool isAdmin, int memberID, std::string membershipType);
    //void addCurrency(float quantity credit card info);
    void setMembershipType(std::string membershipType);
    float getCurrency() const;
    std::pair<std::string, std::string> getName() const;
    int getID() const;
};

#endif
