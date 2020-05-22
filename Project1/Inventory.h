#ifndef _SICT_INVENTORY_H
#define _SICT_INVENTORY_H
#include "item.h"
#include "stock.h"
#include <iostream>
#include <typeinfo>

namespace sict {

	class Inventory : public Stock{
	public:
		Inventory();
		Inventory(const Item*, int);
		Item* remove();
		void addqty();
		void display() const;
		Item* returnItems();
		void addOrders(Item* it, int );

	};






};

#endif