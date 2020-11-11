/* COMPSCI-3307 Group Assignment | Alex Broekhuyse | abroekhu@uwo.ca | 250978523 */
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<algorithm>
#include "../ShoppingCart/Order.h"
#include "ProductCollection.h"
using namespace std; 

ProductCollection::ProductCollection() {
    std::vector<Product> temp;
    this->productList = temp;
    
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
    bool inCollection = false;
    for (unsigned i = 0; i < productList.size(); i++) {
        if (productList[i].getID() == newProduct.getID()) {
            inCollection = true;
        }
    }

    if (inCollection) {
        cout << "This product shares the same ID as another product in the collection" << endl;
    }

    else {
        productList.push_back(newProduct);

        // Writes product to file in CSV format
        ofstream output;
        output.open("products.csv", std::ios_base::app);
        output << newProduct.getID() << "," << newProduct.getName() << "," << newProduct.getCategory() << "," << newProduct.getPrice() << "," << newProduct.getDiscount() << "," << newProduct.getQuantity() << '\n'; // Outputs to .CSV
        output.close();

        cout << "Product was added successfully" << endl;
    }
    
    

}
void ProductCollection::changeInventory(Product product, int quantity) {
    // Changes product quantity 
    for(unsigned i = 0; i < productList.size(); i++) {
        if (productList[i].getID() == product.getID()) {
            productList[i].setQuantity(quantity);
            saveToDatabase();
        }
        else {
            cout << "Could not find the given product in the product collection" << endl;
        }
    }
}
void ProductCollection::removeProduct(string id) {
    // Removes product and updates product list
    bool found = false;
    for (unsigned i = 0; i < productList.size(); i++) {
        if (productList[i].getID() == id) {
            found = true;
            productList.erase(productList.begin() + i);
            cout << "Product was removed from the product collection successfully" << endl;
            saveToDatabase();
        }
    }
    if (!found) {
        cout << "Product was not found in the product collection" << endl;
    }
}

// returns the index of a product in the list  based on the product id passed into the parameter
int ProductCollection::findProduct(string id) {
    // Finds product based on product object, not entirely sure what the point of the function is
    for(unsigned i = 0; i < productList.size(); i++) {
        if (productList[i].getID() == id) {
            return i;
        }
        else {
            return -1;
        }
    }
}

void ProductCollection::restockInventory(Product product, int quantity) {
    bool found = false;
    for (unsigned i = 0; i < productList.size(); i++) {
        if (productList.at(i) == product) {
            found = true;
            cout << "Previous Quantity for " << productList.at(i).getName() << " was " << productList.at(i).getQuantity() << endl;
            productList.at(i).addQuantity(quantity);
            saveToDatabase();
            cout << "New Quantity for " << productList.at(i).getName() << " is " << productList.at(i).getQuantity() << endl;
            break;
        }
    }
    if (!found) {
        cout << "Product was not found in the collection." << endl;
    }
}

void ProductCollection::sortByPrice(string order) {
    if (order == "increasing") {
        sort(productList.begin(), productList.end(), [](Product& lhs, Product& rhs) {
            return lhs.getPrice() < rhs.getPrice();
        });
    }
    else if (order == "decreasing") {
        sort(productList.begin(), productList.end(), [](Product& lhs, Product& rhs) {
            return lhs.getPrice() > rhs.getPrice();
        });
    }

}

void ProductCollection::sortByCategory(string order) {
    if (order == "increasing") {
        sort(productList.begin(), productList.end(), [](Product& lhs, Product& rhs) {
            return lhs.getCategory() < rhs.getCategory();
        });
    }
    else if (order == "decreasing") {
        sort(productList.begin(), productList.end(), [](Product& lhs, Product& rhs) {
            return lhs.getCategory() > rhs.getCategory();
        });
    }

}

void ProductCollection::changePrice(Product product, float newPrice) {
    bool found = false;
    for (unsigned i = 0; i < productList.size(); i++) {
        if (productList.at(i) == product) {
            found = true;
            cout << "Previous Price for " << productList.at(i).getName() << " was " << productList.at(i).getPrice() << endl;
            productList.at(i).setPrice(newPrice);
            saveToDatabase();
            cout << "New Price for " << productList.at(i).getName() << " is " << productList.at(i).getPrice() << endl;
            break;
        }
    }
    if (!found) {
        cout << "Product was not found in the collection" << endl;
    }
}

int ProductCollection::size() {
    return productList.size();
}

Product ProductCollection::at(int index) {
    return productList[index];
}

std::vector<Product> ProductCollection::getProductList(){
    return productList;
}

void ProductCollection::saveToDatabase(){
    // clears the csv file
    ofstream ofs;
    ofs.open("products.csv", ofstream::out | ofstream::trunc);
    ofs.close();
    
    // write the productsList vector into the empty csv file
    ofstream file;
    file.open("products.csv");
    file << "ID,Name,Category,Price,GlobalDiscount,Quantity,\n";    // create the column titles
    
    // create a product entry for each product in the list
    for(unsigned i=0; i < productList.size(); i++){
        file << productList.at(i).getID() << "," << productList.at(i).getName() << "," << productList.at(i).getCategory() << "," << productList.at(i).getPrice() << "," << productList.at(i).getDiscount() << "," << productList.at(i).getQuantity() << "\n";
    }
    
    file.close();   
}