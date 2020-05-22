#ifndef _SICT_STOCK_H
#define _SICT_STOCK_H
#include "item.h"
#include <iostream>
#include <typeinfo>

namespace sict {

	class Stock {
		Item* items;
		size_t size;
	public:
		Stock();
		Stock(const Item*, int);
		void addItem(Item&);
		void removeItem(int);
		~Stock();
		Item& operator[](int);
		int getSize() const;
		void display() const;
		void subQuantity(int, int);
		int find(int) const;
		void loadStock(std::string& b);
		void exportStock(const char* );
		void addQuantity(int, int );
		Item* returnItems();
	};






};

#endif