
#include "VendingInterface.h"
#include <iomanip>
#include <iostream>





constexpr auto TITLE = "|                       ~   Products   ~                       |";
constexpr auto SHOPTOP = "---------------------------------------------------------------";
constexpr auto SHOPLEFT = "| ";
constexpr auto SHOPRIGHT = "     |";
constexpr auto PRICEDIV = "    Price: ";






VendingInterface::VendingInterface(ProductCollection& productCollection) {

	this->pCollection = &productCollection;
	//this->currentMember = &currentMember;
	//this->cart = &cart;

};

//returns pair<int,int> where first integer is the product position in in vector, second integer is the quantity. return -1,-1 on user exit 
std::pair<int,int> VendingInterface::VendingDisplay() {

	
	int choice, amount, vectorIndex;
	// print out products and prices, each with an assigned code. 
	std::cout << SHOPTOP << std::endl << TITLE << std::endl << SHOPTOP << std::endl;

	if (pCollection->size() == 0) {
		std::cout << std::endl << "Sorry No Products Available" << std::endl << std::endl;
		return std::make_pair(-1, -1);
	}

	for (int i = 0; i < pCollection->size(); i++) {

		std::cout << SHOPLEFT << i+1 <<".  "<< std::left << std::setw(17) << pCollection->getProductList().at(i).getName() << PRICEDIV << "$" << std::left << std::setw(17) << pCollection->getProductList().at(i).getPrice() 
			<< "QTY: "<< std::left << std::setw(10) << pCollection->getProductList().at(i).getQuantity() << std::endl;
		
	}

	std::cout << std::endl;


	while (true) {
		std::cout << "Enter number of product or enter 0 to exit " << std::endl << "";
		std::cin >> choice; 
		//if input is not an integer enter this loop
		while (std::cin.fail()|| choice > pCollection->size() || choice < 0){

			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "Error: You must enter number of displayed product" << std::endl;
			std::cout << "Please enter number of product or enter 0 to exit: " << std::endl;
			std::cin >> choice;
		}
		
		
		//if choice is 0 to exit
		if (choice == 0) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			return std::make_pair(-1, -1);
		}
		//if input is integer and in the correct range
		else break;
	}
		
		
	vectorIndex = choice - 1;
	
	std::string name = pCollection->getProductList().at(vectorIndex).getName();

	while (true) {
		std::cout << std::endl << "Please enter amount of "<< name << " to purchase or enter 0 to exit: ";
		std::cin >> amount;
		std::cout << std::endl;
		
		//if input was not an integer or was a negative integer prompt for proper input
		while (std::cin.fail() || amount < 0) {

			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "Error: Enter positive numerical quantity only." << std::endl;
			std::cout << "Please enter number of product or enter 0 to exit: " << std::endl;
			std::cin >> amount;
		}
		
		
		//if input was 0, exit (return -1,-1)
		if (amount == 0) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			return std::make_pair(-1, -1);
		}
		//if input was positive integer exit
		else break;
	}
	
	int stock = pCollection->getProductList().at(vectorIndex).getQuantity();

	//check if amount requested is available. 
	while (amount > stock) {

		std::cout << "Quantity requested is higher than quantity in stock, please select a quantity of at most " << pCollection->getProductList().at(vectorIndex).getQuantity()
			<< " or enter 0 to exit." << std::endl;
		std::cin >> amount;
	}

	if (amount == 0) {
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		return std::make_pair(-1, -1);
	}


	

	std::string confirm; 

	while (true) {
		std::cout << "Please Confirm: " << amount << " units of " << pCollection->at(vectorIndex).getName() << " to be added to cart: (Y to confirm, N to cancel.)" << std::endl;
		std::cin >> confirm;

		while (confirm != "Y" || confirm != "N") {

			if (confirm == "Y") {
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				return std::make_pair(amount, vectorIndex);
			}
			else if (confirm == "N") {
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				return std::make_pair(-1, -1);
			}
			std::cout << "Improper Input: Enter Y/N:  " << std::endl;
			std::cin >> confirm;
		}
	}
	

	
	
	
};
