#include "stock.h"
#include <iomanip>
#include <string>
#include <iostream>
#include <fstream>

namespace sict {

	Stock::Stock() {
		items = nullptr;
		size = 0;

	}
	Stock::~Stock() {
		delete[] items;
	}
	Stock::Stock(const Item* it, int size1) {
		size = size1;
		items = new Item[size1];

		for (int i = 0; i < size; i++) {
			items[i] = it[i];
		}
		cout << "Inventory successfully loaded." << endl;
	}
	void Stock::exportStock(const char* file) {
		std::fstream fo(file, ios::out | ios::trunc);
		fo << "#-id-----Name-----Quantity-----Price" << endl;
	
		for (int i = 0; i < size; i++) {
			fo << items[i].getId() << "," << items[i].getName() << "," << items[i].getPrice() << "," << items[i].getQuantity()<< endl;
		}
		fo.close();

	}
	void Stock::loadStock(string& str) {
		int id;
		string name;
		double price;
		int qty;
		string temp = str;
		std::string::size_type loc;
		loc = temp.find(',');
		id = stoi(temp.substr(0, loc));

		temp.erase(0, loc + 1);
		loc = temp.find(',');
		name = temp.substr(0, loc);

		temp.erase(0, loc + 1);
		loc = temp.find(',');
		price = stod(temp.substr(0, loc));

		temp.erase(0, loc + 1);
		loc = temp.find('\n');
		qty = stoi(temp.substr(0, loc));


		Item *it = new Item(id, qty, price, name);
		addItem(*it);
	
	
	}
	void Stock::subQuantity(int index, int quantity1 ) {
	

				if (quantity1 > items[index].getQuantity()) {
					cout << "Error: Quantity sold cannot be greater than inventory stock";
				}
				else if (quantity1 < 0) {
					cout << "Error: Quantity sold cannot be less than 0";
				}
				else if (quantity1 == items[index].getQuantity()) {
					removeItem(index);
				}
				else {
					items[index].subQuantity(quantity1);
					cout << "Quantity succesfully updated" << endl;
				}
			

	}

	void Stock::addQuantity(int id1, int qty) {
		if (qty > 0) {
			items[id1].addQuantity(qty);
		}
		else {
			cout << "Cannot add a quantity of 0 or less";
		}

}
	
	
	


	void Stock::addItem(Item& item) {
		bool tf = false;	



			//Might need to delete
			if (size == 0) {
				items = new Item[1];
				items[0] = item;
				size++;
				tf = true;

			}
			///////////////////////////////////////////////
		///////////////////////////////////////////////
		else {
			
			if (find(item.getId()) > -1) {
			cout << "Item id exists! Invalid Entry." << endl;
			tf = true;
			}
				
		}

		if ((tf == false)) {
			Item* temp = new Item[size + 1];;
			for (int i = 0; i < size  ; i++) {
				temp[i] = items[i];
			
			}
			delete [] items;
			size = size + 1;

			temp[size -1] = item;

			items = temp;

		}	
}


	int Stock::getSize() const {
		return size;
	
	}


	void Stock::removeItem(int id1) {
		int location;
		bool tf = false;
		for (int i = 0; i < size; i++) {

			if (items[i].getId() == id1) {
				tf = true;
				location = i;

			}
		}
		if (tf == true) {
			Item* temp = new Item[size - 1];
			int x = 0;
			
			for (int j = 0; j < size; j++) {


				if ((&items[location] != &items[j])) {
					temp[x] = items[j];
					x++;
					
				}

			}

			delete[] items;
			size--;
			items = temp;
			
		}
		else
		{

		cout << "Error: ID not found" << endl;
		}
		

	}
	Item* Stock::returnItems() {
		return items;
	
	}
	int Stock::find(int id1) const {
		bool tf = false;
		for (int i = 0; i < size; i++) {
			if (items[i].getId() == id1) {
				return i;
				
			}
		}
		return -1;
	}


	void Stock::display() const{
		if (size == 0) {
			cout << "-No items to display" << endl;
		}
		for (int i = 0; i < size; i++) {
			items[i].display();
		}

	}

	Item& Stock::operator[](int i) {
		return items[i];

	}





}