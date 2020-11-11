#include <iostream>
#include <sstream>
//#include "Member.h"
#include "Interfaces/AccountInterface.h"
//#include "Login.h"
//#include "LoginCollection.h"
#include "Interfaces/LoginInterface.h"
#include "Login/UserDBConversion.h"
#include "Interfaces/SetupInterface.h"
#include "Interfaces/VendingInterface.h"
#include "ShoppingCart/Order.h"
#include "ShoppingCart/ShoppingCart.h"
#include "Interfaces/AdminInterface.h"
#include <climits>

using namespace std;

enum Menu
{
	mainMenu,
	loginMenu,
	accountMenu,
	productMenu,
	cartMenu,
	setupMenu,
	adminMenu
};

int main()
{
	LoginCollection collection;
	UserDBConversion converter;
	Menu menu;

	//load collectios from file
	auto map = converter.FileToLoginCollection();
	collection.setCollection(map, converter.getHighestID());
	ProductCollection Products;
	Products = ProductCollection();

	//initalize classes
	Login login(collection);
	LoginInterface loginInterface(&login);
	SetupInterface SetupInterface(&login);
	AdminInterface adminInterface(Products);
	Member *currentUser;
	AccountInterface accInterface;
	ShoppingCart cart;

	int input = 0;
	int amount, index;
	Menu baseMenu;

	// if the login collection is empty run a first time setup for the first admin account
	if (collection.getMap().size() == 0)
	{
		menu = setupMenu;
	}
	else
	{
		menu = loginMenu;
	}
	while (true)
	{

		while (menu == setupMenu)
		{
			SetupInterface.SetupPrompt();
			menu = loginMenu;
			break;
		}

		while (menu == loginMenu)
		{

			string inputStr;
			cout << endl
				 << "----------------- Main Menu -----------------" << endl;
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
				currentUser = NULL;
				currentUser = loginInterface.loginPrompt();
				if (currentUser != NULL)
				{
					// add other setters here for the current user in the system
					// OR could change login interface to a singleton and have a static member for the current user----------------------
					accInterface.setCurrentMember(currentUser);
					string adminCheck = "";
					if (currentUser->getisadmin())
					{
						while (adminCheck != "y" && adminCheck != "n")
						{
							cout << "Login as an admin? (Y/N)" << endl;
							getline(cin, adminCheck);
							adminCheck = tolower(adminCheck[0]);

							if (adminCheck.length() != 1 || (adminCheck != "y" && adminCheck != "n"))
							{
								cout << "Invalid input" << endl;
								continue;
							}
						}
					}
					else
					{
						menu = baseMenu = mainMenu;
						break;
					}

					if (adminCheck == "y")
					{
						menu = baseMenu = adminMenu;
						break;
					}
					else
					{
						menu = baseMenu = mainMenu;
						break;
					}
				}
			}
			else if (input == 2)
			{
				std::cin.clear();
				cout << "----------------- Account Creation -----------------" << endl;
				loginInterface.createAccountPrompt();
			}
			else if (input == 3)
			{
				auto test = login.getLoginCollection().getMap();
				converter.LoginCollectionToFile(test);
				Products.saveToDatabase();
				return 0;
			}
		}

		while (menu == productMenu)
		{

			while (true)
			{
				VendingInterface SaleInterface(Products);
				pair<int, int> result = SaleInterface.VendingDisplay();

				amount = result.second;
				index = result.first;

				if (index != -1)
				{

					Product Product = Products.getProductList().at(index);
					Order newOrder(Product, 0, amount);
					cart.addOrder(newOrder);

					cout << cart.printCart() << endl;
				}
				else
				{
					break;
				}
			}

			menu = baseMenu;
		}

		while (menu == mainMenu)
		{

			string inputStr;
			int input;
			cout << endl
				 << "--------------------- Main Menu ---------------------" << endl;
			cout << "1. Product Catalogue" << endl;
			cout << "2. Shopping Cart and Checkout" << endl;
			cout << "3. Account Menu" << endl;
			cout << "4. Logout" << endl;

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
				menu = productMenu;
				break;
			}
			else if (input == 2)
			{
				menu = cartMenu;
				break;
			}
			else if (input == 3)
			{
				menu = accountMenu;
				break;
			}
			else if (input == 4)
			{
				menu = loginMenu;
				break;
			}
		}

		while (menu == accountMenu)
		{
			string inputStr;
			int input;
			cout << "----------------- Account Menu -----------------" << endl;
			cout << "1. Display Account Information" << endl;
			cout << "2. Add currency" << endl;
			cout << "3. Return to Main Menu" << endl;
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
				menu = baseMenu;
				break;
			}
		}

		while (menu == cartMenu)
		{
			string inputStr;
			int input;
			cout << endl
				 << "----------------- Shopping Cart Menu -----------------" << endl;
			cout << "1. View Shopping Cart" << endl;
			cout << "2. Checkout" << endl;
			cout << "3. Remove Items from Shopping Cart" << endl;
			cout << "4. Return to Main Menu" << endl;
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
				cout << cart.printCart() << endl;
				cout << "Press Enter to Continue";
				cin.ignore();
			}
			else if (input == 2)
			{

				int check = cart.processCart(currentUser);

				//check if process cart failed or succeeded here.

				if (check == 0)
				{
					break;
				}
				else
				{
					cout << cart.createInvoice() << endl;
					cart.clearOrders();
					cout << endl
						 << "Press Enter to Continue";
					cin.ignore();
				}
			}
			else if (input == 3)
			{
				int cartCheck = cart.removeOrderInterface();
				break;
			}
			else if (input == 4)
			{

				menu = baseMenu;
				break;
			}
		}

		while (menu == adminMenu)
		{

			string inputStr;
			int input;
			cout << endl
				 << "--------------------- Admin Menu ---------------------" << endl;
			cout << "1. Product Catalogue" << endl;
			cout << "2. Shopping Cart and Checkout" << endl;
			cout << "3. Account Menu" << endl;
			cout << "4. Add/Remove/Restock/Change Price" << endl;
			cout << "5. Logout" << endl;

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
				menu = productMenu;
				break;
			}
			else if (input == 2)
			{
				menu = cartMenu;
				break;
			}
			else if (input == 3)
			{
				menu = accountMenu;
				break;
			}
			else if (input == 4)
			{
				adminInterface.AdminPrompt();
				break;
			}
			else if (input == 5)
			{
				menu = loginMenu;
				break;
			}
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
