/* COMPSCI-3307 Group Assignment | Alex Broekhuyse | abroekhu@uwo.ca | 250978523 */
#include <string>
#include "Product.h"
using namespace std;

string id;
string productName;
string category;
float price;
float discount;
int quantity;
// Still need to add personalDiscount (need discount class to do so)

// default constructor
Product::Product() {
    id = "";
    productName = "";
    category = "";
    price = 0.00;
    discount = 0.00;
    quantity = 0;
}
// constructor with parameters
Product::Product(std::string new_id, std::string new_name, std::string new_category, float new_price, float new_discount, int new_quantity) {
    id = new_id;
    productName = new_name;
    category = new_category;
    discount = new_discount;
    price = new_price;
    quantity = new_quantity;
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
string Product::getID() {
    return id;
}
string Product::getName() { 
    return productName; 
}
string Product::getCategory() {
    return category;
}
float Product::getDiscount() {
    return discount;
}
float Product::getPrice() { 
    return price; 
}
int Product::getQuantity() { 
    return quantity; 
}