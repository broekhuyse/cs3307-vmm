/* COMPSCI-3307 Group Assignment | Alex Broekhuyse | abroekhu@uwo.ca | 250978523 */
#ifndef PRODUCTCOLLECTION_H
#define PRODUCTCOLLECTION_H
#include <string>
class Product;

class ProductCollection {
    private:
        Product product;
        int quantity;
        std::ifstream input;
        std::string fileName;
        std::vector<Product> productList; 
        std::string line, key;
    public:
        ProductCollection();
        ~ProductCollection();
        void addProduct(Product product);
        void changeInventory(Product product, int quantity);
        void removeProduct(std::string);
        Product findProduct(Product product);
};
#endif