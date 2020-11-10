#include <iostream>
#include <sstream>
//#include "Member.h"
#include "AccountInterface.h"
//#include "Login.h"
//#include "LoginCollection.h"
#include "LoginInterface.h"
#include "UserDBConversion.h"

using namespace std;

enum Menu
{
	loginMenu,
	accountMenu,
	productMenu
};

int main()
{
	LoginCollection collection;
	UserDBConversion converter;

	//load collection from file
	collection.setCollection(converter.FileToLoginCollection());

	Login login(collection);
	LoginInterface loginInterface(&login);

	Member *currentUser;
	AccountInterface accInterface;

	int input = 0;
	Menu menu = loginMenu;

	while (true)
	{
		while (menu == loginMenu)
		{
			string inputStr;
			cout << "----------------- Main Menu -----------------" << endl;
			cout << "1. Login" << endl;
			cout << "2. CreateAccount" << endl;
			cout << "3. Exit" << endl;
			while (getline(cin, inputStr))
			{
				stringstream stream(inputStr);
				if (stream >> input)
				{
					if (stream.eof())
					{
						break;
					}
				}
				cout << "Invalid input" << endl;
			}

			if (input == 1)
			{
				cout << "----------------- Login -----------------" << endl;
				currentUser = loginInterface.loginPrompt();
				if (currentUser != NULL)
				{
					// add other setters here for the current user in the system
					// OR could change login interface to a singleton and have a static member for the current user----------------------
					accInterface.setCurrentMember(currentUser);
					menu = productMenu;
					break;
				}
			}
			else if (input == 2)
			{
				cout << "----------------- Account Creation -----------------" << endl;
				loginInterface.createAccountPrompt();
			}
			else if (input == 3)
			{
				auto test = login.getLoginCollection().getMap();
				converter.LoginCollectionToFile(test);
				return 0;
			}
		}
		while (menu == productMenu)
		{
			cout << "PRODUCT MENU NOT IMPLEMENTED" << endl;
			menu = accountMenu;
		}

		while (menu == accountMenu)
		{
			string inputStr;
			int input;
			cout << "----------------- Account Menu -----------------" << endl;
			cout << "1. Display Account Information" << endl;
			cout << "2. Add currency" << endl;
			cout << "3. Logout" << endl;
			while (getline(cin, inputStr))
			{
				stringstream stream(inputStr);
				if (stream >> input)
				{
					if (stream.eof())
					{
						break;
					}
				}
				cout << "Invalid input" << endl;
			}

			if (input == 1)
			{
				cout << "----------------- Account Information -----------------" << endl;
				accInterface.printAccountInfo();
			}
			else if (input == 2)
			{
				cout << "----------------- Add Currency -----------------" << endl;
				accInterface.addCurrencyPrompt();
			}
			else if (input == 3)
			{
				menu = loginMenu;
				break;
			}
		}
	}

	// for (int i = 0; i < 1; i++)
	// {
	// 	cout << "----------------- Account Creation -----------------" << endl;
	// 	loginInterface.createAccountPrompt();
	// }

	// cout << "----------------- Login -----------------" << endl;
	// currentUser = loginInterface.loginPrompt();

	// if (currentUser != NULL)
	// {
	// 	accInterface.setCurrentMember(currentUser);
	// 	accInterface.addCurrencyPrompt();
	// }

	//save collection to file
	// auto test = login.getLoginCollection().getMap();
	// converter.LoginCollectionToFile(test);

	// return 0;
}
