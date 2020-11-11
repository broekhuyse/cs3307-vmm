#ifndef ADMININTERFACE_H
#define ADMININTERFACE_H

#include "../Product/Product.h"
#include "../Product/ProductCollection.h"

class AdminInterface
{
private:
	ProductCollection* pCollection;

public:

	AdminInterface(ProductCollection& productCollection);
	void ProductDisplay();
	void AdminPrompt();

};
#endif