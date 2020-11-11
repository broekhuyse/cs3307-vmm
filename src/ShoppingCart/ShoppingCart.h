#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <string>
#include <list>
#include "Order.h"
#include "../Login/Member.h"
//#include "CouponCollection"

class ShoppingCart {
	private:
		std::list<Order> orders;
		//CouponCollection couponCodes;
		
	public:
		ShoppingCart();
		//ShoppingCart(CouponCollection codeBase);
		
		void removeOrder(Order rem);
		void addOrder(Order add);
		bool isEmpty();
		int getSize();
		
		void updateCosts();
		void addCouponCode(std::string code);
		//void updateCouponCollection(CouponCollection newCodes);
		std::string createInvoice();
		int processCart(Member* buyer);
};

#endif