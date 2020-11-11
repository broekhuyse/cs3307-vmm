/**
 * Class that provides an interface to handle the account that is currently logged in to the vending machine system
 */
#include "AccountInterface.h"
#include <iostream>
#include <sstream>

using namespace std;

AccountInterface::AccountInterface()
{
}

AccountInterface::AccountInterface(Member *member)
{
    currentMember = member;
}

void AccountInterface::setCurrentMember(Member *member)
{
    currentMember = member;
}

/**
 * Provides an interface for the user to add currency to their account
 * @param
 * @return void 
 */
void AccountInterface::addCurrencyPrompt()
{
    float quant;
    int month, year;
    CreditCardCompany company;
    string number, name, securityCode, temp;

    cout << "Quantity: " << endl;
    // check if valid input
    while (getline(cin, temp))
    {
        stringstream stream(temp);
        if (stream >> quant)
        {
            if (stream.eof())
            {
                break;
            }
        }
        cout << "Invalid input" << endl;
    }

    cout << "Number: " << endl;
    getline(cin, number);

    cout << "Name: " << endl;
    getline(cin, name);

    cout << "Security Code: " << endl;
    getline(cin, securityCode);

    cout << "Expiration Month: " << endl;
    // check if valid input
    while (getline(cin, temp))
    {
        stringstream stream(temp);
        if (stream >> month)
        {
            if (stream.eof())
            {
                break;
            }
        }
        cout << "Invalid input" << endl;
    }

    cout << "Expiration Year: " << endl;
    // check if valid input
    while (getline(cin, temp))
    {
        stringstream stream(temp);
        if (stream >> year)
        {
            if (stream.eof())
            {
                break;
            }
        }
        cout << "Invalid input" << endl;
    }

    cout << "Credit card company: " << endl;
    cout << "Input 1 for Visa" << endl;
    cout << "Input 2 for American Express" << endl;
    cout << "Input 3 for Master Card" << endl;
    getline(cin, temp);
    int choice = stoi(temp);
    switch (choice)
    {
    case 1:
        company = visa;
        break;
    case 2:
        company = americanExpress;
        break;
    case 3:
        company = masterCard;
        break;
    default:
        break;
    }

    int result = currentMember->addCurrency(quant, number, month, year, name, securityCode, company);

    if (result == -1)
    {
        cout << "ERROR. The currency could not be added" << endl;
    }
    else
    {
        cout << "The currency was added." << endl;
        cout << "New Balance: " << currentMember->getCurrency() << endl;
    }
}

/**
 * Prints the account's ID, name and currency to the screen
 * @param
 * @return void 
 */
void AccountInterface::printAccountInfo()
{
    cout << "ID: " << currentMember->getID() << endl;
    cout << "Name: " << currentMember->getName().first << " " << currentMember->getName().second << endl;
    cout << "Currency: " << currentMember->getCurrency() << endl;
}