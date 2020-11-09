#ifndef ACCOUNT_INTERFACE_H
#define ACCOUNT_INTERFACE_H

#include "Member.h"
class AccountInterface
{
private:
    Member *currentMember;

public:
    AccountInterface();
    AccountInterface(Member *member);
    void setCurrentMember(Member *member);
    void addCurrencyPrompt();
    void printAccountInfo();
};
#endif