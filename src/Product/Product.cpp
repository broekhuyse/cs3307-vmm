/* COMPSCI-3307 Group Assignment | Alex Broekhuyse | abroekhu@uwo.ca | 250978523 */
#include <string>
#include "Product.h"
#include <iostream>

using namespace std;

// Still need to add personalDiscount (need discount class to do so)

// default constructor
Product::Product() {
    this->id = "";
    this->productName = "";
    this->category = "";
    this->price = 0.00;
    this->bulkModifier = 0.00;
    this->globalDiscount = 0.00;
    this->quantity = 0;
}
// constructor with parameters
Product::Product(std::string productName, std::string category, std::string id, float price, int quantity, float bulkModifier, float globalDiscount) {
	this->productName = productName;
	this->category = category;
	this->id = id;
	this->price = price;
	this->quantity = quantity;
	this->bulkModifier = bulkModifier;
	this->globalDiscount = globalDiscount;
}

/*
	Name: Product()
	Description: Constructor that takes all necessary parameters. bulkModifier and globalDiscount attributes are defaulted to 0.
	Params: productName: Name of the product
			category: The category the product belongs to
			id: the unique id of the product
			cost: the cost of the product
	Return: none
*/

Product::Product(std::string productName, std::string category, std::string id, float price, int quantity) {
	this->productName = productName;
	this->category = category;
	this->id = id;
	this->price = price;
	this->quantity = quantity;
	this->bulkModifier = 0;
	this->globalDiscount = 0;
}

// destructor
Product::~Product() {
}
// setter & getter functions for data input
void Product::setID(string new_id) {
    id = new_id;
}
void Product::setName(string new_name) { 
    productName = new_name; 
}
void Product::setCategory(string new_category) {
    category = new_category;
}
/*void Product::setDiscount(float new_discount) {
    discount = new_discount;
}*/
void Product::setPrice(float new_price) { 
    price = new_price; 
}
void Product::setQuantity(int new_quantity) { 
    quantity = new_quantity; 
}
string Product::getID() const{
    return id;
}
string Product::getName() { 
    return productName; 
}
string Product::getCategory() {
    return category;
}
float Product::getDiscount() {
    return globalDiscount;
}
float Product::getPrice() { 
    return price; 
}
int Product::getQuantity() { 
    return quantity; 
}

void Product::addQuantity(int quantity) {
	this->quantity += quantity;
}

bool Product::operator == (const Product& other) {
	return this->getID() == other.getID();
}

ostream& operator<<(ostream& os, const Product& prod) {
	os << prod.productName << "    " << prod.category << "    " << prod.id << "    " << prod.price << "    " << prod.quantity << "    " << prod.bulkModifier << "    " << prod.globalDiscount << endl;
	return os;
}
