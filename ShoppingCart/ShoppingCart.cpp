#include <iostream>
#include <sstream>
#include "ShoppingCart.h"



ShoppingCart::ShoppingCart() {
}

bool ShoppingCart::isEmpty(){
	return orders.empty();
}

int ShoppingCart::getSize() {
	return orders.size();
}

/*
* Name: addOrder
* Description: If the Order's product is already in the collection, merge orders. Otherwise adds order to collection
* Params: add: Order to be added
*/
void ShoppingCart::addOrder(Order add) {
	for(std::list<Order>::iterator i = orders.begin(); i != orders.end(); ++i) {
		if(*(add.getProduct()) == *((*i).getProduct())) {
			(*i).setQuantity((*i).getQuantity() + add.getQuantity());
			(*i).changeTotalCost((*i).getTotalCost() + add.getTotalCost());
			return;
		}
	}
	orders.push_back(add);
}

/*
* Name: removeOrder
* Description: Remove the provided Order
* Params: rem: Order to be removed
*/
void ShoppingCart::removeOrder(Order rem) {
	orders.remove(rem);
}

void ShoppingCart::addCouponCode(std::string code) {
	// Nothing for now until coupons are implemented
}

/*
* Name: updateCosts
* Description: Calls Order::updateCost on every Order in the collection. Uses the new cost in the associated Product.
*/
void ShoppingCart::updateCosts() {
	for(std::list<Order>::iterator i = orders.begin(); i != orders.end(); ++i) {
		(*i).updateCost();
	}
}

/*
* Name: processCart
* Description: Processes cart for issues, (not enough funds, not enough stock). If no issues are found, 
* 			   checkouts items in cart by removing their quantity from stock and subtracts the total price from 
*			   the provided member's balance. Then empties the cart - Recommended to create invoice BEFORE calling this function.
* Params: buyer: Member* who is making the purchase
* Returns: 0 on failure, 1 or higher on success.
*/
int ShoppingCart::processCart(Member* buyer) {
	float grandPrice = 0.0;
	const int tax = 0.15;
	bool verified = true;
	std::ostringstream purchased;
	
	// Scan list for any issues - ex: low funds, low stock, etc
	for(std::list<Order>::iterator i = orders.begin(); i != orders.end(); i++) {
		grandPrice += (*i).getTotalCost();
		if((*i).getQuantity() > (*i).getProduct()->getQuantity()) {
			verified = false;
			std::cerr << "Low Stock: Need " << (*i).getProduct()->getName() << " x " << (*i).getQuantity() << ", only have " << (*i).getProduct()->getQuantity() << " in stock.\n";
		}
	}
	grandPrice += grandPrice*tax;
	if(grandPrice > buyer->getCurrency()){
		verified = false;
		std::cerr << "Low user funds: Cart total is $" << grandPrice << ", while User has balance of $" << buyer->getCurrency() << "\n";
	}
	
	// Continue with checkout ONLY if verified (no issues)
	if(!verified) {
		std::cout << "Checkout failed. \n";
		return 0;
	}
	purchased << "Purchased items: ";
	for(std::list<Order>::iterator i = orders.begin(); i != orders.end(); ++i) {
		// Remove stock
		(*i).getProduct()->setQuantity((*i).getProduct()->getQuantity() - (*i).getQuantity());
		purchased << (*i).getProduct()->getName() << " x " << (*i).getQuantity() << ", ";
	}
	buyer->modifyBalance(-grandPrice);      // Add balance as negative float
	std::string purchasedItems = purchased.str();
	std::cout << "Checkout success!\n" << purchasedItems.substr(0, purchasedItems.length()-3) << "\n";
	
	// Eliminate the list
	orders.clear();
	return 1;
}

/*
* Name: createInvoice
* Description: Creates an invoice of the contained Orders
* Returns: string invoice, containing name, amount, totalCost of all Orders and grand total of Orders at end
*/
std::string ShoppingCart::createInvoice() {
	std::ostringstream invoice;
	float grandCost = 0;
	float tax;
	
	for(std::list<Order>::iterator i = orders.begin(); i != orders.end(); ++i) {
		invoice << "Product: " << (*i).getProduct()->getName() << ", Amount: " << ((*i).getQuantity()) << ", Total Cost: $" << ((*i).getTotalCost()) << "\n";
		grandCost += (*i).getTotalCost();
	}
	
	tax = grandCost*0.15;		// Hardcoded tax
	invoice << "\nSubtotal: $" << grandCost << "\nTax: $" << tax << "\nTotal: $" << (grandCost+tax) << "\n";
	return "Invoice:\n" + invoice.str();
}
