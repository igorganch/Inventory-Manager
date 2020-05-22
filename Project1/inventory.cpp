#include "Inventory.h"

namespace sict {
	Inventory::Inventory() {
		
	}
	Inventory::Inventory(const Item* it , int ok) {
		*this = Inventory(it, ok);
	
	}
	Item* Inventory::remove() {
		int id1;
		cout << "Enter id: ";
		cin >> id1;
		int index = find(id1);
		int quantity1;
		if (index > -1) {
			cout << endl << "Enter quantity sold: ";
			cin >> quantity1;
			cout << endl;


			Item temp = (*this)[index];


			
			//(*this)[index].
			(*this)[index].subQuantity(quantity1);
			temp.subQuantity(temp.getQuantity());
			temp.addQuantity(quantity1);

			Item* temp1 = new Item();
			*temp1 = temp;
		
			return temp1;
		}
		else {
			cout << "Error: ID not found" << endl;
			return nullptr;
		}
	}
	void Inventory::addqty() {
		int id1;
		cout << "Enter The id: ";
		cin >> id1;
		int quantity1;
		int index = find(id1);
		if (index > -1) {

			cout << endl << "Enter quantity you wish to add: ";
			cin >> quantity1;
			Inventory::addQuantity(index, quantity1);
		}

		else {
			cout << "Error: ID not found" << endl;
		}
	
	}
	void Inventory::addOrders(Item* it, int size ) {
		
		cout << size;
		for (int i = 0; i < size; i++) {
			int index = Stock::find(it[i].getId());
			if (index > -1) {
				
				(*this)[index].addQuantity(it->getQuantity());


			}
			else {
				Stock::addItem(it[i]);

			}
		}
	}


	void Inventory::display() const {
		cout << "===Inventory===" << endl;
		Stock::display();
	
	}
	Item* Inventory::returnItems()  {
		return Stock::returnItems();
	}


}
