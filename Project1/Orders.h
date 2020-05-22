#ifndef _SICT_ORDERS_H
#define _SICT_ORDERS_H
#include "item.h"
#include "stock.h"
#include "inventory.h"
#include "sold.h"
#include <iostream>
#include <typeinfo>
#include <vector>


namespace sict {

	class Orders : public Stock {
		vector<Item> history;
		bool status;
		unsigned orderId;
		int noSold;
		int noProducts;
	public:
		static unsigned orderNo;
		Orders();
		~Orders();
		Orders(string);
		int sold() const;
		int getnoProducts() const;
		void exportOrder(const char*);
		void orderHistory(Inventory* );
		void addOrder();
		void displayHistory() const;
		void displayOrder() ;
		Item* delivered();
		int getId() const;
		bool getStatus() const;

	};
}
#endif