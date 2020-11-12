#include "../Login/Member.h"
#include "SetupInterface.h"
#include <iostream>
#include <sstream>

using namespace std;

SetupInterface::SetupInterface()
{
}

SetupInterface::SetupInterface(Login *login)
{
	this->login = login;
}

SetupInterface::~SetupInterface() {

}

void SetupInterface::SetupPrompt()
{
	int result = -1;
	string firstName, lastName, username, password;
	cout << "WELCOME TO YOUR BRAND NEW VIRTUAL VENDING MACHINE\n"
		 << endl;
	cout << "Please Follow The Upcoming Instructions To Setup Your First Account" << endl;

	while (result < 0)
	{
		cout << "Please Enter Your First Name: " << endl;
		getline(cin, firstName);

		cout << "Please Enter Your Last Name: " << endl;
		getline(cin, lastName);

		cout << "Please Enter A Username: " << endl;
		getline(cin, username);

		cout << "Please Enter A Password (Must be longer than 8 characters and contain an uppercase, lowercase, a number and a special symbol): " << endl;
		getline(cin, password);

		cout << "As the first member, your account will be designated as an admin account" << endl;

		result = login->createAccount(username, password, firstName, lastName, true, "temp");
		if (result == -1)
		{
			cout << "Username already exists. Please try again" << endl;
		}

		else if (result == -2)
		{
			cout << "Password is not secure enough. Please try again" << endl;
		}

		else if (result == -3)
		{
			cout << "Empty fields." << endl;
		}
		else if (result == -4)
		{
			cout << "Name contained non-alpha characters." << endl;
		}

		else
		{
			cout << "Your setup is complete!" << endl;
		}
		cout << endl;
	}
}
