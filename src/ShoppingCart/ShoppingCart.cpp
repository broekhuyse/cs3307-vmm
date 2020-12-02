/*! \file ShoppingCart.h
 * \brief Stores Orders for checkout.
 * \details Stores a list of Orders and contains functions to purchase associated Products.
 * \authors 
 */
#include <iostream>
#include <sstream>
#include <math.h>
#include "ShoppingCart.h"
#include "../PurchaseHistory/PurchaseHistory.h"

/**
* Constructor for ShoppingCart. Creates an empty list of Orders.
*/
ShoppingCart::ShoppingCart()
{
}

/**
* Destructor for ShoppingCart.
*/
ShoppingCart::~ShoppingCart()
{
}

/**
* Checks if the cart is empty and has no Orders inside.
* @return true if empty, false otherwise.
*/
bool ShoppingCart::isEmpty()
{
	return orders.empty();
}

/**
* Returns the number of Orders in the cart.
* @return int of every order in the cart.
*/
int ShoppingCart::getSize()
{
	return orders.size();
}

/**
* If the Order's product is already in the collection, merge orders. Otherwise adds order to collection.
* @params add Order to be added.
* @return None.
*/
void ShoppingCart::addOrder(Order add)
{
	add.updateCost();
	for (std::list<Order>::iterator i = orders.begin(); i != orders.end(); ++i)
	{
		if (add.getProduct() == i->getProduct())
		{
			i->setQuantity(i->getQuantity() + add.getQuantity());
			i->changeTotalCost(i->getTotalCost() + add.getTotalCost());
			return;
		}
	}
	orders.push_back(add);
}

/**
* Remove the provided Order.
* @params rem Order to be removed.
* @return None.
*/
void ShoppingCart::removeOrder(Order rem)
{
	orders.remove(rem);
}

//void ShoppingCart::addCouponCode(std::string code) {
// Nothing for now until coupons are implemented
//}

/**
* Calls Order::updateCost on every Order in the collection. Uses the new cost in the associated Product.
* @return None.
*/
void ShoppingCart::updateCosts()
{
	for (std::list<Order>::iterator i = orders.begin(); i != orders.end(); ++i)
	{
		(*i).updateCost();
	}
}

/**
* Processes cart for issues, (not enough funds, not enough stock). If no issues are found, 
* 				checkouts items in cart by removing their quantity from stock and subtracts the total price from 
*			   the provided member's balance. 
* @param buyer Member* who is making the purchase.
* @param productC ProductCollection to apply changes to.
* @param histC PurchaseHistoryCollection that records cart upon succesful purchase.
* @return 0 on failure, 1 or higher on success.
*/
int ShoppingCart::processCart(Member *buyer, ProductCollection &productC, PurchaseHistoryCollection &histC)
{
	float grandPrice = 0.0;
	const float tax = 0.15;
	bool verified = true;
	std::ostringstream purchased;
	std::cout << std::endl;

	std::cout << this->printCart() << std::endl
			  << std::endl
			  << "Please review your cart above. Enter 'Y' if you would like to process your cart, Enter 'N' to cancel." << std::endl;

	std::string confirm;

	while (true)
	{

		std::cin >> confirm;

		while (confirm != "Y" || confirm != "N")
		{

			if (confirm == "Y")
			{
				break;
			}
			else if (confirm == "N")
			{

				return 0;
			}
			std::cout << "Improper Input: Enter Y/N:  " << std::endl;
			std::cin >> confirm;
		}
		break;
	}

	// Scan list for any issues - ex: low funds, low stock, etc
	for (std::list<Order>::iterator i = orders.begin(); i != orders.end(); i++)
	{
		grandPrice += i->getTotalCost();
		if (i->getQuantity() > i->getProduct().getQuantity())
		{
			verified = false;
			std::cerr << "Low Stock: You attempted to purchase: " << i->getProduct().getName() << " x " << i->getQuantity() << ", only have " << i->getProduct().getQuantity() << " in stock.\n";
		}
	}
	grandPrice += grandPrice * tax;
	if (grandPrice > buyer->getCurrency())
	{
		verified = false;
		std::cerr << "Low user funds: Cart total is $" << grandPrice << ", while User has balance of $" << buyer->getCurrency() << "\n";
	}

	// Continue with checkout ONLY if verified (no issues)
	if (!verified)
	{
		std::cout << "Checkout failed. \n";
		std::cout << "Press Enter to Continue" << std::endl;
		std::cin.ignore();
		return 0;
	}
	purchased << "Purchased items: ";

	std::string orderID;
	int reduced;

	Product test;
	for (std::list<Order>::iterator i = orders.begin(); i != orders.end(); ++i)
	{

		orderID = i->getProduct().getID();

		for (unsigned x = 0; x < productC.getProductList().size(); x++)
		{

			if (orderID == productC.getProductList().at(x).getID())
			{
				reduced = ((productC.getProductList().at(x).getQuantity()) - (i->getQuantity()));
				productC.changeInventory(productC.getProductList().at(x), reduced);
			}
		}

		purchased << i->getProduct().getName() << " x " << i->getQuantity() << ", ";
	}

	buyer->modifyBalance(-grandPrice); // Add balance as negative float
	std::string purchasedItems = purchased.str();
	std::cout << "Checkout success!\n"
			  << purchasedItems.substr(0, purchasedItems.length() - 2) << "\n";
			  
	// Send a copy of the order list to the history collection
	PurchaseHistory hist = PurchaseHistory(orders, buyer->getID());
	histC.addPurchaseHistory(hist);

	return 1;
}

/**
* Prints contents of cart and price.
* @return string containing name, amount, totalCost of all Orders and grand total of Orders at end
*/
std::string ShoppingCart::printCart()
{
	std::ostringstream invoice;
	float grandCost = 0;
	float tax;

	for (std::list<Order>::iterator i = orders.begin(); i != orders.end(); i++)
	{
		i->updateCost();
		if (i->getProduct().getDiscount() != NULL)
		{
			invoice << "Product: " << i->getProduct().getName() << ", Amount: " << (i->getQuantity()) << ", Total: $" << i->getQuantity() * i->getProduct().getPrice() << "\nDiscount: " << i->getProduct().getDiscount()->getAmount() * 100 << "%, Total Cost: $" << (i->getTotalCost()) << "\n";
		}
		else
		{
			invoice << "Product: " << i->getProduct().getName() << ", Amount: " << (i->getQuantity()) << ", Total Cost: $" << (i->getTotalCost()) << "\n";
		}
		grandCost += i->getTotalCost();
	}

	tax = grandCost * 0.15; // Hardcoded tax
	invoice << "\nSubtotal: $" << grandCost << "\nTax: $" << roundf(tax * 100) / 100 << "\nTotal: $" << roundf((grandCost + tax) * 100) / 100 << "\n";
	return "----------------- Shopping Cart -----------------:\n" + invoice.str();
}
/**
* Creates an invoice of the contained Orders.
* @return string invoice, containing name, amount, totalCost of all Orders and grand total of Orders at end.
*/
std::string ShoppingCart::createInvoice()
{
	std::ostringstream invoice;
	float grandCost = 0;
	float tax;

	for (std::list<Order>::iterator i = orders.begin(); i != orders.end(); i++)
	{
		i->updateCost();
		invoice << "Product: " << i->getProduct().getName() << ", Amount: " << (i->getQuantity()) << ", Total Cost: $" << (i->getTotalCost()) << "\n";
		grandCost += i->getTotalCost();
	}

	tax = grandCost * 0.15; // Hardcoded tax
	invoice << "\nSubtotal: $" << grandCost << "\nTax: $" << roundf(tax * 100) / 100 << "\nTotal: $" << roundf((grandCost + tax) * 100) / 100 << "\nPaid: $" << roundf((grandCost + tax) * 100) / 100 << "\nOwed: $0\n";
	return "Invoice:\n" + invoice.str();
}

/**
* Clears the list of orders in shopping cart.
* @return None.
*/
void ShoppingCart::clearOrders()
{
	orders.clear();
}

int ShoppingCart::removeOrderInterface()
{

	std::cout << "----------------------------Remove Order----------------------------" << std::endl;

	float grandCost = 0;
	int counter = 1;
	int input;

	for (std::list<Order>::iterator i = orders.begin(); i != orders.end(); i++)
	{

		std::cout << counter << ".  "
				  << "Product: " << i->getProduct().getName() << ", Amount: " << (i->getQuantity()) << ", Total Cost: $" << (i->getTotalCost()) << "\n";
		grandCost += i->getTotalCost();
		counter++;
	}

	std::cout << "Select the number of the product you would like to remove from your order or press 0 to return to the Main Menu: " << std::endl;
	std::cin >> input;

	int size = orders.size();
	while (std::cin.fail() || input > size || input < 0)
	{

		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "Error: You must enter number of displayed product" << std::endl;
		std::cout << "Please enter number of product or enter 0 to exit: " << std::endl;
		std::cin >> input;
	}
	int index = input - 1;

	if (input == 0)
	{
		return 0;
	}
	else
	{

		std::list<Order>::iterator i = std::next(orders.begin(), index);

		removeOrder((*i));

		std::cout << std::endl
				  << "Order Removed" << std::endl;

		return 1;
	}
}
