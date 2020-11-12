#include "AdminInterface.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

constexpr auto TITLE = "|                                      ~   Products   ~                                      |";
constexpr auto SHOPTOP = "----------------------------------------------------------------------------------------------";
constexpr auto SHOPLEFT = "| ";
constexpr auto SHOPRIGHT = "   |";
constexpr auto PRICEDIV = "    Price: ";

//constructor, takes in a product collection
AdminInterface::AdminInterface(ProductCollection &productCollection)
{

	this->pCollection = &productCollection;
};

AdminInterface::~AdminInterface() {

}

// Method that displays all the current products in the product collection
void AdminInterface::ProductDisplay()
{

	// print out products and prices, each with an assigned code.
	std::cout << SHOPTOP << std::endl
			  << TITLE << std::endl
			  << SHOPTOP << std::endl;

	if (pCollection->size() == 0)
	{
		std::cout << std::endl
				  << "Sorry No Products Available" << std::endl
				  << std::endl;
	}

	for (int i = 0; i < pCollection->size(); i++)
	{

		std::cout << SHOPLEFT << std::left << std::setw(4) << i + 1 << ".  " << "ID: " << std::left << std::setw(10) << pCollection->getProductList().at(i).getID() << std::left << std::setw(20) << pCollection->getProductList().at(i).getName() << PRICEDIV << "$" << std::left << std::setw(10) << pCollection->getProductList().at(i).getPrice()
			<< "QTY: " << std::left << std::setw(10) << pCollection->getProductList().at(i).getQuantity() << std::left << std::setw(10) << pCollection->getProductList().at(i).getCategory() << SHOPRIGHT << std::endl;
	}

	cout << SHOPTOP << endl;
}


// interface that displays appropriate prompts and user inputs that relate to the different admin functions
void AdminInterface::AdminPrompt()
{
	// represents what action the user wants to do. Possible actions are shown below
	int action;

	while (true)
	{

		// possible actions
		cout << "Please select one of the following options: " << endl;
		cout << "1: Add Product" << endl;
		cout << "2: Remove Product" << endl;
		cout << "3: Restock Product" << endl;
		cout << "4: Change Price of Product" << endl;
		cout << "0: Exit the admin menu" << endl;
		cin >> action;

		//if incorrect input, then prompt again
		while (action != 1 && action != 2 && action != 3 && action != 4 && action != 0)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Error: You must pick one of the valid options" << endl;
			cout << "Please select one of the following options: " << endl;
			cout << "1: Add Product" << endl;
			cout << "2: Remove Product" << endl;
			cout << "3: Restock Product" << endl;
			cout << "4: Change Price of Product" << endl;
			cout << "0: Exit the admin menu" << endl;
			cin >> action;
		}

		// exit the admin menu
		if (action == 0)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			break;
		}

		// prompts for adding a product
		while (action == 1)
		{
			string id, productName, category;
			float price;
			int quantity;
			ProductDisplay();
			cout << "Please enter a unique product id\n"
				 << endl;
			cin >> id;

			if (cin.fail())
			{
				cout << "Invalid id input\n"
					 << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}

			cout << "Please enter the product name\n"
				 << endl;
			cin >> productName;

			if (cin.fail())
			{
				cout << "Invalid product name input\n"
					 << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}

			cout << "Please enter the product's category\n"
				 << endl;
			cin >> category;

			if (cin.fail())
			{
				cout << "Invalid category input\n"
					 << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}

			cout << "Please enter the price for the new product\n"
				 << endl;
			cin >> price;

			if (cin.fail() || price < 0)
			{
				cout << "Invalid price input. Must be a positive numeric value\n"
					 << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}

			cout << "Please enter the quantity for the new product\n"
				 << endl;
			cin >> quantity;

			if (cin.fail() || quantity < 0)
			{
				cout << "Invalid quantity input. Must be a positive integer value\n"
					 << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}

			Product newProduct = Product(productName, category, id, price, quantity, 0, 0);
			this->pCollection->addProduct(newProduct);

			cin.clear();
			cin.ignore(1000, '\n');

			cout << "If you want to add product again, press 1\n To go back to the main menu input 0" << endl;
			cin >> action;
			if (cin.fail() || (action != 1 && action != 0))
			{
				cout << "Invalid input. Returning to main menu" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}

			if (action == 0)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}
		}

		// prompts for removing a product
		while (action == 2)
		{
			ProductDisplay();
			string id;
			cout << "Please enter the product id of the product you want to remove" << endl;
			cin >> id;
			this->pCollection->removeProduct(id);

			cin.clear();
			cin.ignore(1000, '\n');

			cout << "If you want to remove product again, press 2\n To go back to the main menu input 0" << endl;
			cin >> action;
			if (cin.fail() || (action != 2 && action != 0))
			{
				cout << "Invalid input. Returning to main menu" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}

			if (action == 0)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}
		}

		// prompts for restocking a product
		while (action == 3)
		{
			int choice, quantity;
			ProductDisplay();
			cout << "Enter number of product you wish to restock or enter 0 to exit " << endl
				 << "";
			cin >> choice;
			//if input is not an integer or is an integer that is negative, or greater than the size of the product list, then prompt again
			while (cin.fail() || choice > pCollection->size() || choice < 0)
			{

				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Error: You must enter number of displayed product" << endl;
				cout << "Please enter number of product you wish to restock or enter 0 to exit: " << endl;
				cin >> choice;
			}

			//if choice is 0 to exit
			if (choice == 0)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}
			//if input is integer and in the correct range
			else
			{
				int vectorIndex = choice - 1;

				Product selectedProduct = pCollection->getProductList().at(vectorIndex);

				cout << "Please enter the quantity you would like to add to the stock of the selected product" << endl;
				cin >> quantity;
				// if the quantity is 0 or less, then prompt again
				while (cin.fail() || quantity < 1)
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Please enter a valid number" << endl;
					cin >> quantity;
				}
				this->pCollection->restockInventory(selectedProduct, quantity);
			}

			cin.clear();
			cin.ignore(1000, '\n');

			cout << "If you want to restock another product, press 3\nTo go back to the main menu input 0" << endl;
			cin >> action;
			if (cin.fail() || (action != 3 && action != 0))
			{
				cout << "Invalid input. Returning to main menu" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}

			if (action == 0)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}
		}

		// prompts for changing the price of a product
		while (action == 4)
		{
			int choice, price;
			ProductDisplay();
			cout << "Enter number of product you wish to change the price of or enter 0 to exit " << endl
				 << "";
			cin >> choice;
			//if input is not an integer, or is greater than the product collection size, or is negative, then prompt again
			while (cin.fail() || choice > pCollection->size() || choice < 0)
			{

				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Error: You must enter number of displayed product" << endl;
				cout << "Please enter number of product you wish to change the price of or enter 0 to exit: " << endl;
				cin >> choice;
			}

			//if choice is 0 to exit
			if (choice == 0)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}
			//if input is integer and in the correct range
			else
			{
				int vectorIndex = choice - 1;

				Product selectedProduct = pCollection->getProductList().at(vectorIndex);

				cout << "Please enter the new price of the selected product" << endl;
				cin >> price;
				while (cin.fail() || price < 0)
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Please enter a valid number" << endl;
					cin >> price;
				}
				this->pCollection->changePrice(selectedProduct, price);
			}

			cin.clear();
			cin.ignore(1000, '\n');

			cout << "If you want to change price of another product, press 4\nTo go back to the main menu input 0" << endl;
			cin >> action;
			if (cin.fail() || (action != 4 && action != 0))
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid input. Returning to main menu" << endl;
				break;
			}

			if (action == 0)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}
		}
	}
}