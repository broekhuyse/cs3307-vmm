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
    productList.push_back(newProduct);
    
    // Writes product to file in CSV format
    ofstream output;
    output.open("products.csv", std::ios_base::app);
    output << newProduct.getID() << "," << newProduct.getName() << "," << newProduct.getCategory() << "," << newProduct.getPrice() << "," << newProduct.getDiscount() << "," << newProduct.getQuantity() << '\n'; // Outputs to .CSV
    output.close();

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
    ofstream output;
    output.open("products.csv");
    for(int i = 0; i < productList.size(); i++) {
        if (productList[i].getID() == id) {
            productList.erase(productList.begin() + i);
        }
    }
    for(int i = 0; i < productList.size(); i++) {
        output << productList[i].getID() << "," << productList[i].getName() << "," << productList[i].getCategory() << "," << productList[i].getPrice() << "," << productList[i].getDiscount() << "," << productList[i].getQuantity() << '\n';
    }
    output.close();
}
Product ProductCollection::findProduct(Product product) {
    // Finds product based on product object, not entirely sure what the point of the function is
    for(int i = 0; i < productList.size(); i++) {
        if (productList[i].getID() == product.getID()) {
            return product;
        }
    }
}

void ProductCollection::restockInventory(Product product, int quantity) {
    bool found = false;
    for (int i = 0; i < productList.size(); i++) {
        if (productList.at(i) == product) {
            found = true;
            cout << "Previous Quantity For " << productList.at(i).getName() << " Was " << productList.at(i).getQuantity() << endl;
            productList.at(i).addQuantity(quantity);
            cout << "New Quantity For " << productList.at(i).getName() << " Is " << productList.at(i).getQuantity() << endl;
            break;
        }
    }
    if (!found) {
        cout << "Product was not found in the collection" << endl;
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

int ProductCollection::size() {
    return productList.size();
}

Product ProductCollection::at(int index) {
    return productList[index];
}

void ProductCollection::changePrice(Product product, float newPrice) {
    bool found = false;
    for (int i = 0; i < productList.size(); i++) {
        if (productList.at(i) == product) {
            found = true;
            cout << "Previous Price For " << productList.at(i).getName() << " Was " << productList.at(i).getPrice() << endl;
            productList.at(i).setPrice(newPrice);
            cout << "New Price For " << productList.at(i).getName() << " Is " << productList.at(i).getPrice() << endl;
            break;
        }
    }
    if (!found) {
        cout << "Product was not found in the collection" << endl;
    }
}

std::vector<Product> ProductCollection::getProductList(){
    return productList;
}
