
#ifndef VENDINGINTERFACE_H
#define VENDINGINTERFACE_H

#include "Member.h"
#include "ShoppingCart.h"
#include "product.h"
#include "ProductCollection.h"
class VendingInterface
{
private:
	
	ProductCollection* productCollection;
	Member* currentMember; 
	ShoppingCart* cart;

public:
	VendingInterface(ProductCollection& productCollection, Member& currentMember, ShoppingCart cart);
	int VendingDisplay();
	
	
};
#endif