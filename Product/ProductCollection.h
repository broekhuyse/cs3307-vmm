/* COMPSCI-3307 Group Assignment | Alex Broekhuyse | abroekhu@uwo.ca | 250978523 */
#ifndef PRODUCTCOLLECTION_H
#define PRODUCTCOLLECTION_H
#include <string>
#include <vector>
#include "Product.h"
#include <fstream>

class Product;

class ProductCollection {
    private:
        std::vector<Product> productList; 
        
    public:
        ProductCollection();
        ~ProductCollection();
        void addProduct(Product product);
        void changeInventory(Product product, int quantity);
        void removeProduct(std::string);
        Product findProduct(Product product);
        
        void restockInventory(Product product, int quantity);
        void sortByPrice(std::string order);
        void sortByCategory(std::string order);
        int size();
        Product at(int index);
        void changePrice(Product product, float newPrice);
        std::vector<Product> getProductList();
};
#endif
