#include "Order.h"


Order::Order() {
	Product emptyProd;
	this->product = (&emptyProd);
	this->dateOfPurchase = 0;
	this->quantity = 0;
	this->totalCost = 0;
}

Order::Order(Product* prod, int pDate, int quant) {
	this->product = prod;
	this->dateOfPurchase = pDate;
	this->quantity = quant;
	
	updateCost();
}

// Overrides == to compare product, quantity, and date
// Returns true iff all of the above match with the other
bool Order::operator== (const Order& other){
	return (*product == *(other.getProduct()) && this->quantity == other.getQuantity() && this->dateOfPurchase == other.getDate());
}

// Overrides != to compare product, quantity, and date
// Returns true iff ANY of the above does not match with the other
bool Order::operator!= (const Order& other){
	return (!(*product == *(other.getProduct()))|| !(this->quantity == other.getQuantity()) || !(this->dateOfPurchase == other.getDate()));
}

void Order::updateCost() {
	float cost = this->product->getPrice();
	// If there is any discount stuff, calculate it here
	this->totalCost = cost * this->quantity;
}

int Order::getDate() const{
	return this->dateOfPurchase;
}

int Order::getQuantity() const{
	return this->quantity;
}

Product* Order::getProduct() const{
	return this->product;
}

float Order::getTotalCost() {
	return this->totalCost;
}

void Order::setDate(int newDate) {
	this->dateOfPurchase = newDate;
}

void Order::setQuantity(int amount) {
	this->quantity = amount;
}

void Order::changeTotalCost(float cost) {
	this->totalCost = cost;
}
