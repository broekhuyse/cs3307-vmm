/* COMPSCI-3307 Group Assignment | Alex Broekhuyse | abroekhu@uwo.ca | 250978523 */
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<algorithm>
#include "../Login/Order.h"
#include "ProductCollection.h"
using namespace std; 

std::vector<Product> productList;

ProductCollection::ProductCollection() {
    ifstream input;
    string fileName;
    input.open("products.csv");

    string line, key;
    getline(input,line); // Skip first line of CSV file (headings)

    while (getline(input, line)) { // Read lines of CSV file into a 'Product' object
        Product product;

        istringstream iss(line);
        getline(iss, key, ',');
        product.setID(key);
        getline(iss, key, ',');
        product.setName(key);
        getline(iss, key, ',');
        product.setCategory(key);
        getline(iss, key, ',');
        product.setPrice(std::stof(key));
        getline(iss, key, ',');
        // product.setDiscount(std::stof(key));
        getline(iss, key, ',');
        product.setQuantity(std::stoi(key));

        productList.push_back(product); // Add product to product list, rinse & repeat
    }
    input.close();
}
ProductCollection::~ProductCollection(){
} 
// No need to take in quantity (like in UML diagram) because quantity is specified when creating Product object
void ProductCollection::addProduct(Product newProduct) {
    productList.push_back(newProduct);
    
    // Writes product to file in CSV format
    ofstream output;
    output.open("products.csv", std::ios_base::app);
    output << newProduct.getID() << "," << newProduct.getName() << "," << newProduct.getCategory() << "," << newProduct.getPrice() << "," << newProduct.getDiscount() << "," << newProduct.getQuantity() << '\n'; // Outputs to .CSV

}
void ProductCollection::changeInventory(Product product, int quantity) {
    // Changes product quantity 
    for(int i = 0; i < productList.size(); i++) {
        if (productList[i].getID() == product.getID()) {
            productList[i].setQuantity(quantity);
        }
    }
}
void ProductCollection::removeProduct(string id) {
    // Removes product and updates product list
    // Still have to figure out how to remove from CSV file
    for(int i = 0; i < productList.size(); i++) {
        if (productList[i].getID() == product.getID()) {
            productList.erase(productList.begin() + i);
        }
    }
}
Product ProductCollection::findProduct(Product product) {
    // Finds product based on product object, not entirely sure what the point of the function is
    for(int i = 0; i < productList.size(); i++) {
        if (productList[i].getID() == product.getID()) {
            return product;
        }
    }
}