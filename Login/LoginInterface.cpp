#include <iostream>
#include "LoginInterface.h"
#include "Member.h"
#include "CreditCardCompany.h"

using namespace std;

LoginInterface::LoginInterface()
{
}

LoginInterface::LoginInterface(Login *login)
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

        cout << "Password (must be longer than 8 characters and contain uppercase, lowercase, a number and a special symbol): " << endl;
        getline(cin, password);

        cout << "First name: " << endl;
        getline(cin, fname);

        cout << "Last name: " << endl;
        getline(cin, lname);

        result = login->createAccount(username, password, fname, lname, false, "temp");
        if (result == -1)
        {
            cout << "Username already exists, please try again." << endl;
        }
        else if (result == -2)
        {
            cout << "Password is not secure enough, please try again." << endl;
        }
        else
        {
            cout << "Account created." << endl;
        }
    }
}

Member *LoginInterface::loginPrompt()
{
    Member *result = NULL;
    string username, password;
    while (result == NULL)
    {
        cout << "Username: " << endl;
        getline(cin, username);

        cout << "Password: " << endl;
        getline(cin, password);

        result = login->checkLogin(username, password);
        if (result == NULL)
        {
            cout << "Username does not exist or password does not match, please try again." << endl;
        }
        else
        {
            cout << "Logging in..." << endl;
        }
    }

    // Temp debugging print for member information
    cout << "ID: " << result->getID() << endl;
    cout << "Name: " << result->getName().first << " " << result->getName().second << endl;
    cout << "Currency: " << result->getCurrency() << endl;

    // test adding currency to account without checks
    cout << "---------- Add Currency ----------" << endl;
    float quant;
    int month, year;
    CreditCardCompany company;
    string number, name, securityCode, temp;

    cout << "Quantity: " << endl;
    getline(cin, temp);
    quant = stof(temp);

    cout << "Number: " << endl;
    getline(cin, number);

    cout << "Name: " << endl;
    getline(cin, name);

    cout << "Security Code: " << endl;
    getline(cin, securityCode);

    cout << "Expiration Month: " << endl;
    getline(cin, temp);
    month = stoi(temp);

    cout << "Expiration Year: " << endl;
    getline(cin, temp);
    year = stoi(temp);

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

    result->addCurrency(quant, number, month, year, name, securityCode, company);
    // Temp debugging print for member information
    cout << "ID: " << result->getID() << endl;
    cout << "Name: " << result->getName().first << " " << result->getName().second << endl;
    cout << "Currency: " << result->getCurrency() << endl;

    // return the currently logged in member
    return result;
}