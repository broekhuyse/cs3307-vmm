#include "Member.h"
#include "ShoppingCart.h"
#include "product.h"
#include "ProductCollection.h"
#include "VendingInterface.h"
#include "iomanip"
#include <iostream>
#include <sstream>

using namespace std;

constexpr auto TITLE = "|                      ~VENDING MACHINE~                      |";
constexpr auto SHOPTOP = "---------------------------------------------------------------";
constexpr auto SHOPLEFT = "|     ";
constexpr auto SHOPRIGHT = "     |";
constexpr auto DIVIDER = "     |     ";



int choiceToInt(string input) {

	if (input == "A1") return 0;
	else if (input == "A2") return 1;
	else if (input == "B1") return 2;
	else if (input == "B2") return 3;
	else if (input == "C1") return 4;
	else if (input == "C2") return 5;
	else if (input == "D1") return 6;
	else if (input == "D2") return 7;
	else if (input == "E1") return 8;
	else if (input == "E2") return 9;

	else return -1;
}

VendingInterface::VendingInterface(ProductCollection& productCollection, Member& currentMember, ShoppingCart cart) {

	this->productCollection = &productCollection;
	this->currentMember = &currentMember;
	this->cart = &cart;

};
//returns pair<int,int> where first integer is the product position in in vector, second integer is the quantity. 
pair<int,int> VendingInterface::VendingDisplay() {

	string choice; 
	int amount, vectorIndex;
	// print out products and prices, each with an assigned code. 
	std::cout << SHOPTOP << std::endl << TITLE << std::endl << SHOPTOP << std::endl;
	std::vector<std::string> codes{ "A1","A2","B1","B2","C1","C2", "D1","D2", "E1","E2" };
	for (int i = 0; i < 10; i = i + 2) {

		std::cout << SHOPLEFT << std::left << std::setw(17) << productCollection->getProductList[i].getPName() << " " << codes[i] << DIVIDER << std::left << std::setw(17) << productCollection->getProductList[i + 1].getPName() << " " << codes[i + 1] << SHOPRIGHT << std::endl;
		std::cout << SHOPLEFT << std::left << "$" << std::setw(19) << productCollection->getProductList[i].getPrice() << DIVIDER << std::left << "$" << std::setw(19) << productCollection->getProductList[i + 1].getPrice() << SHOPRIGHT << std::endl;
		std::cout << SHOPTOP << std::endl;

	}

	while (true) {
		cout << "What product would you like to purchase? " << std::endl << "Please enter your selection or enter 0 to exit: ";
		cin >> choice; 

		// if improper input, prompt again
		if (choice != "A1" || "A2" || "B1" || "B2"|| "C1" || "C2" || "D1" || "D2" || "E1" || "E2") {
			cout << "Improper input please try again: " << endl;
			continue;
		}

		//if choice was 0, return -1,-1
		if (choice == "0") {
			//return -1 on exit with no order added to cart
			return make_pair(-1, -1);
		}
		//if input was proper, exit loop
		else break;
	}
	
	while (true) {
		cout << endl << "Please enter amount of selected item to purchase or enter 0 to exit: ";
		cin >> amount;

		//if input = 0 return -1,-1
		if (amount == 0) {
			return make_pair(-1, -1);
		}
		//if input was not an integer prompt for proper input
		else if (cin.fail()) {

			// Clear errors
			cin.clear();
			

			cout << "Improper Input, Please enter amount as an integer value" << endl;
			continue;
		}
		//if input was proper, exit loop
		else break;
	}
	
	while (amount > productCollection->getProductList[vectorIndex].getQuantity()) {

		cout << "Quantity requested is higher than quantity in stock, please select a quantity less than : " << productCollection->getProductList[vectorIndex].getQuantity()
			<< " or enter 0 to exit." << endl; 
	}

	if (amount == 0)  return make_pair(-1, -1); 



	vectorIndex = choiceToInt(choice);

	//cout << amount << " units of: " << productCollection->getProductList[vectorPosition].getPName() << " added to cart" << endl;

	//COULD HAVE ITEM BE ADDED TO CART HERE INSTEAD OF RETURNING PAIR ?

	//return pair of (amount, index 
	return make_pair(amount, vectorIndex);
};
