//#include <iostream> // TEMP FOR DEBUGGING
#include <ctime>
#include <math.h>
#include "Member.h"

using namespace std;

Member::Member()
{
}

/*
* Name: Member
* Description: Constructor for Member class to initialize new member
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
/*
* Name: Member
* Description: Constructor for Member class to add user from DB to collection
* Params: name: Name of the new member
*         isAdmin: Admin status of the member
*         memberID: ID of the member
*         membershipType: membership type of the new member
*		  currency: amount of currency on member account
* Return: none
*/
Member::Member(std::string fname, std::string lname, bool isAdmin, int memberID, std::string membershipType, float currency)
{
    this->fname = fname;
    this->lname = lname;
    this->isAdmin = isAdmin;
    this->memberID = memberID;
    this->membershipType = membershipType;
    this->currency = currency;
}

/*
* Name: addCurrency
* Description: Takes credit card information and amount of currency to add as parameters and checks if the card is valid, if valid then adds to the member's currency
* Params: quantity: amount of currency to be added
*         number: credit card number
*         month: expiry month
*         year: expiry year
*         name: name of the card holder
*         securityCode: security code for credit card
*         company: the providing credit card company
* Return: none
*/
void Member::addCurrency(float quantity, std::string number, int month, int year, std::string name, std::string securityCode, CreditCardCompany company)
{
    // check if quantity in valid format
    if (currency < 0)
    {
        return;
    }

    // add currency rounded to two decimal places to account if credit card is valid 
    if (validateCreditCard(number, month, year, name, securityCode, company))
    {
        currency += roundf(quantity * 100) / 100;
    }
}

/*
* Name: validateCreditCard
* Description: Takes credit card information as parameters and checks if the card is valid
* Params: number: credit card number
*         month: expiry month
*         year: expiry year
*         name: name of the card holder
*         securityCode: security code for credit card
*         company: the providing credit card company
* Return: true if the card is valid, false if the card is invalid
*/
bool Member::validateCreditCard(std::string number, int month, int year, std::string name, std::string securityCode, CreditCardCompany company)
{
    // check the credit card number and security code to the providing company
    switch (company)
    {
    case visa: // start with 4 and 16 digits and 3 digit security code
        if (number[0] != '4' || number.length() != 16 || securityCode.length() != 3)
        {
            //cerr << "Type error." << endl;
            return false;
        }
        break;
    case americanExpress: // start with 37 and 15 digits and 4 digit security code
        if (number[0] != '3' || number[1] != '7' || number.length() != 15 || securityCode.length() != 4)
        {
            //cerr << "Type error." << endl;
            return false;
        }
        break;
    case masterCard: // start with 5 and 16 digits and 3 digit security code
        if (number[0] != '5' || number.length() != 16 || securityCode.length() != 3)
        {
            //cerr << "Type error." << endl;
            return false;
        }
        break;
    }

    // check the credit card number using Luhn algorithm

    // double every second digit and sum the individual digits
    int sum = 0;
    for (int i = number.length() - 2; i >= 0; i -= 2)
    {
        int temp = (number[i] - '0') * 2; // convert to int and then multiply by 2

        // if double digit then convert take sum of digits
        if (temp > 9)
        {
            temp = 1 + temp % 10;
        }
        sum += temp;
    }
    // sum odd digits from right to left
    for (int i = number.length() - 1; i >= 0; i -= 2)
    {
        sum += number[i] - '0';
    }

    if (sum % 10 != 0)
    {
        //cerr << "Number Error" << endl;
        return false;
    }

    // COULD MOVE INTO ITS OWN CLASS FOR USE IN EXPIRATION DATES FOR PRODUCTS, ETC
    // check the expiry date to the current date
    time_t currSec = time(NULL);        // get number of seconds since epoch
    tm *currTime = localtime(&currSec); // convert to days/months/years

    // month in range of 1-12
    if (month > 12 || month < 1)
        return false;

    // check if card is expired
    if ((currTime->tm_year - 100) > year || ((currTime->tm_year - 100) == year && (currTime->tm_mon + 1) > month))
    {
        //cerr << "Expired Card" << endl;
        //cerr << currTime->tm_year-100<< " " << currTime->tm_mon +1 << endl;
        return false;
    }

    // otherwise card is valid
    return true;
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
std::string Member::getfname() const
{
    return fname;
}
std::string Member::getlname() const
{
    return lname;
}
bool Member::getisadmin() const
{
    return isAdmin;
}
std::string Member::getMembershipType() const
{
    return membershipType;
}
void Member::setMembershipType(std::string membershipType)
{
    this->membershipType = membershipType;
}