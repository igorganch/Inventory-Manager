#ifndef _SICT_ITEM_H
#define _SICT_ITEM_H

#include <iostream>
#include <utility>

using namespace std;

namespace sict {

	class Item {
		int id;
		string name;
		int quantity;
		double price;

	public:
		Item();
		~Item();
		Item(int, int, double, string );
		Item& operator=(Item&& src);
		Item(Item&& src);
	    Item& operator=(const Item& src);
		Item(const Item& src);
		void addQuantity(int amount);
		void subQuantity(int amount);
		void editPrice(double);
		int getId() const;
		double getPrice() const;
		string getName() const;
		int getQuantity() const;
		void display() const;
		void displayIdName() const;
	};

	std::ostream& info( const Item&, std::ostream&);

}
#endif
