/* COMPSCI-3307 Group Assignment | Alex Broekhuyse | abroekhu@uwo.ca | 250978523 */
#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>

class Product {
    private:
        std::string id;
        std::string productName;
        std::string category;
        float discount;
        float price; 
        int quantity; 
    public:
        Product();
        Product(std::string, std::string, std::string, float, float, int);
        ~Product();
        
        std::string getID();
        std::string getName();
        std::string getCategory();
        float getDiscount();
        float getPrice();
        int getQuantity();
        void setID(std::string id);
        void setName(std::string productName);
        void setCategory(std::string category);
        void setPrice(float price);
        void setQuantity(int quantity);
};

#endif