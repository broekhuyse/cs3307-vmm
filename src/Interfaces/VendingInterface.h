
#ifndef VENDINGINTERFACE_H
#define VENDINGINTERFACE_H

#include "../Product/Product.h"
#include "../Product/ProductCollection.h"

class VendingInterface
{
private:
	
	ProductCollection* pCollection;

public:
	
	VendingInterface(ProductCollection& productCollection);
	std::pair<int, int> VendingDisplay();
	
	
};
#endif
