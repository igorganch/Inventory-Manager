#ifndef _SICT_SOLD_H
#define _SICT_SOLD_H
#include "item.h"
#include "stock.h"
#include "inventory.h"
#include <iostream>
#include <typeinfo>

namespace sict {

	class Sold : public Stock {
		double profit;

	public:
		Sold();
		~Sold();
		Sold(const Item*, int);
		void addSold(Item*);
		void display() const;
		void findProfit();















	};









}

#endif
