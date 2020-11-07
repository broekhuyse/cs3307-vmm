#ifndef ORDER_H
#define ORDER_H

#include "../Product/Product.h"

class Order {
	private:
		Product product;
		int dateOfPurchase;				// Should prob be string
		int quantity;
		float totalCost;
		
		void calculateCost();
		
	public:
		Order();
		Order(Product prod, int pDate, int quant);
		
		bool operator == (const Order& other);
		bool operator != (const Order& other);
		
		int getDate();
		int getQuantity();
		Product getProduct();
		float getTotalCost();
		
		void setDate(int newDate);
		void setQuantity(int amount);
		void changeTotalCost(float cost);
		
		
};

#endif
