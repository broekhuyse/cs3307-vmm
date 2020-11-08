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
		if(add.getProduct().getName() == *i.getProduct().getName()) {
			*i.setQuantity(*i.getQuantity() + add.getQuantity());
			*i.changeTotalCost(*i.getTotalCost() + add.getTotalCost());
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

void ShoppingCart::processCart() {
	// Not entirely sure what will happen here
	// Maybe need to add Order::validate() ?
}

/*
* Name: createInvoice
* Description: Creates an invoice of the contained Orders
* Returns: string invoice, containing name, amount, totalCost of all Orders and grand total of Orders at end
*/
std::string ShoppingCart::createInvoice() {
	std::string invoice = "Invoice:\n";
	float grandCost = 0;
	float tax;
	
	for(std::list<Order>::iterator i = orders.begin(); i != orders.end(); ++i) {
		invoice << "Product: " << *i.getProduct().getName() << ", Amount: " << *i.getQuantity() << ", Total Cost: $" << *i.getTotalCost() << "\n";
		grandCost += *i.getTotalCost();
	}
	
	tax = grandCost*0.15;		// Hardcoded tax
	invoice << "\nSubtotal: $" << grandCost << "\nTax: $" << tax << "\nTotal: $" << (grandCost+tax) << "\n";
	return invoice;
}
