
#ifndef VENDINGINTERFACE_H
#define VENDINGINTERFACE_H


#include "../Login/Member.h"
#include "../Product/Product.h"
#include "../Product/ProductCollection.h"
#include "../ShoppingCart/ShoppingCart.h"

class VendingInterface
{
private:
	
	ProductCollection* pCollection;
	Member* currentMember; 
	//ShoppingCart* cart;

public:
	
	VendingInterface(ProductCollection& productCollection, Member& currentMember);
	std::pair<int, int> VendingDisplay();
	
	
};
#endif
