#include "item.h"

namespace sict {
	Item::Item() {
		id = 0;
		name = '/0';
		quantity = 0;
		price = 0;

	}
	Item::Item(int id1, int quantity1, double price1, string name1) {
		id = id1;
		quantity = quantity1;
		name = name1;
		price = price1;
	}
	void Item::addQuantity(int amount) {
		quantity =  quantity + amount;
	}
	void Item::subQuantity(int amount) {
		quantity = quantity -  amount;
	}

	
	Item::Item(const Item& src) {
		*this = src;
	}
	Item& Item::operator=(const Item& src) {
		if (this != &src) {
			id = src.id;
			name = src.name;
			quantity = src.quantity;
			price = src.price;
		}
		return *this;
	}
	

	Item::Item(Item&& src) {
		*this = std::move(src);
	}
	Item& Item::operator=(Item&& src) {
		if (this != &src) {
			id = src.id;
			name = src.name;
			quantity = src.quantity;
			price = src.price;

			src.id = 0;
			src.name = '/0';
			src.quantity = 0;
			src.price = 0;
		}
		return *this;
	
	}
	Item::~Item() {
	
	}
	int Item::getId() const {
		return id;
	
	}
	double Item::getPrice() const{
		return price;

	}
	string Item::getName() const{

		return name;

	}
	int Item::getQuantity() const {
		return quantity;
	}
	void Item::displayIdName() const {
		cout << "----------------------------------------" << endl;
		cout << "id - " << getId() << " name - " << getName() << endl;
	}
	void Item::display() const {
		cout << "----------------------------------------" <<endl;
		cout << "id - " << id << " name - " << name << " Quanity - " << quantity << " Price - " << price << endl;
	}

	/// work on later

	std::ostream& info(Item& it, std::ostream& os) {
		os << "id - " << it.getId() << " name - " << it.getName() << " Quanity - " << it.getQuantity() << " Price - " << it.getPrice();
		return os;
	}




}