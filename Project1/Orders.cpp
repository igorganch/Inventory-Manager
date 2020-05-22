#include "Orders.h"
#include <algorithm>
#include <iomanip>
#include <string>
#include <iostream>
#include <fstream>

namespace sict {

	unsigned Orders::orderNo = 0;
	bool compare(Item* it, Item* it2) {

		return it->getName() > it2->getName();

	}
	Orders::~Orders() {
		orderNo--;
	}


	int Orders::sold()const {
		return noSold;
	}
	Orders::Orders() : orderId{++orderNo}{
		status = false;
	}
	void Orders::orderHistory(Inventory* inv) {
		history.clear();
		Item* it = inv->returnItems();
		for (int i = 0; i < inv->getSize(); i++) {
			history.push_back(it[i]);
		}

	}
	void Orders::exportOrder(const char* file) {
		std::fstream fo(file, ios::in | ios::out | ios::app);
		if (status == true) {
			fo << "true," << noProducts << endl;
		}
		else {
			fo << "false," << noProducts << endl;
		}
		for (int i = 0; i < Stock::getSize(); i++) {
			fo << (*this)[i].getId() << "," << (*this)[i].getName() << "," << (*this)[i].getPrice() << "," << (*this)[i].getQuantity()  << endl;
		}
		fo.close();
	}
	Orders::Orders(string str) : orderId{ ++orderNo } {
		string stat;
		string temp = str;
		std::string::size_type loc;
		loc = temp.find(',');
		stat = temp.substr(0, loc);

			if (stat == "true") {
				status = true;
			}
			else {
				status = false;
			}
			temp.erase(0, loc + 1);
			loc = temp.find('\n');
			noProducts = stoi(temp.substr(0, loc));


	
	}
	int Orders::getnoProducts() const {
		return noProducts;
	}
	void Orders::displayHistory() const{
		for ( int i = 0; i < history.size(); i++) {
			history[i].displayIdName();
		}
	
	}

	void Orders::displayOrder()  {
		if (status == true) {
			cout << "Id -" << orderId << "       # of items " << Stock::getSize() << "  -----Status: Delivered" << endl;
			for (int i = 0; i < Stock::getSize(); i++) {
				(*this)[i].display();
				
			}
		}
		else {
			cout << "Id -" << orderId << "       # of items " << Stock::getSize() << "  -----Status: Not Delivered" << endl;
		}
	}
	Item* Orders::delivered() {
		noSold = 0;
		cout << " ===Order " + orderId << "===" << endl;
		Stock::display();
		string yesno;
		bool tf = false;
		vector<Item> delivered;
		vector<Item> soldpr;
		do{
			cout << endl << "All items delivered? [Y] - yes  [N] - no: ";
		cin >> yesno;
		if (yesno == "y" || yesno == "Y") {
			tf = true;
			status = true;
			noSold = Stock::getSize();
			Item* array = new Item[Stock::getSize()];
			(*this)[1].getId();
			for (int i = 0 ; i < Stock::getSize(); i++){
				array[i]  = (*this)[i];
				soldpr.push_back((*this)[i]);
				soldpr[i].display();
			}

			
			for (int i = 0; i < soldpr.size(); i++) {
				Stock::removeItem(soldpr[i].getId());
			}
			noProducts = Stock::getSize();
			return array;


		}
		else if (yesno == "n" || yesno == "N") {
			tf = true;
			string recievedYN;
			int recievedQTY;
			int size = Stock::getSize();
			int i = 0;
			do{

				cout << "ID - " << (*this)[i].getId() << endl;
				cout << "Name - " << (*this)[i].getName() << endl;
				cout << "Quantity - " << (*this)[i].getQuantity() << endl << "Is this the correct quantity Recieved? [Y] -yes [N] -no  :";
				cin >> recievedYN;
				if (recievedYN == "y" || recievedYN == "Y") {
					noSold++;
					delivered.push_back((*this)[i]);
					soldpr.push_back((*this)[i]);
					i++;
					//Stock::removeItem((*this)[i].getId());
					//i = 0;
					//size = Stock::getSize();
					

				}
				else if(recievedYN == "n" || recievedYN == "N"){
					cout << "Enter Quantity recieved: ";
					cin >> recievedQTY;
					if (recievedQTY == (*this)[i].getQuantity()) {
						delivered.push_back((*this)[i]);
						soldpr.push_back((*this)[i]);
						//Stock::removeItem((*this)[i].getId());
						noSold++;
						i++;
						//i = 0;
						//size = Stock::getSize();
					}
					else {
						noSold++;
						Item temp = (*this)[i];

						(*this)[i].subQuantity(recievedQTY);
						temp.subQuantity(temp.getQuantity());
						temp.addQuantity(recievedQTY);
						Item* temp1 = new Item();
						*temp1 = temp;
						delivered.push_back(*temp1);
						i++;
					}

				}
			} while (i < size);
		

		}
		else {
			cout << endl << "\"" << yesno << "\"" << " is not a valid option" << endl;
			tf = false;
		}

	} while (tf != true);

	for (int i = 0; i < soldpr.size(); i++) {
		Stock::removeItem(soldpr[i].getId());
	}

	Item* array = new Item[delivered.size()];
	for (int i = 0; i < delivered.size(); i++) {
		array[i] = delivered[i];
	}

	noProducts = Stock::getSize();
	if (Stock::getSize() == 0) {
		status = true;
	}

	return array;

	}

	bool Orders::getStatus() const {
		return status;
	
	}
	int Orders::getId() const {
	
		return orderId;
	}


	void Orders::addOrder() {
		int choice;
		string yesno;
		bool tf = false;
		do {
			cout << "1 - Add a new Item to the database to the order " << endl;
			cout << "2 - Add an existing item in the database to the order" << endl;
			cout << "Enter option: ";
			cin >> choice;


			if (choice == 1) {
				int id;
				string name;
				int quantity;
				double price;
				cout << endl;
				cout << "Enter id : ";
				cin >> id;
				cout << "Enter name : ";
				cin >> name;
				cout << "Enter quantity : ";
				cin >> quantity;
				cout << "Enter price : ";
				cin >> price;
				cout << endl;
				Item* it = new Item(id, quantity, price, name);
				Stock::addItem(*it);
				do {
					cout << "Add another Item? [Y] -yes [N] - no :";
					cin >> yesno;
					if (yesno == "y" || yesno == "Y") {
						tf = true;
					}
					else if (yesno == "n" || yesno == "N") {
						tf = false;
					}
					else {
						cout << endl << "\"" << yesno << "\"" << " is not a valid option" << endl;
					}

				} while (!(yesno == "y" || yesno == "Y" || yesno == "n" || yesno == "N"));

			}
			else if (choice == 2) {
				int id;
				bool found = false;
				int quantity;
				displayHistory();
				cout << "Enter id : ";
				cin >> id;

				for (int i = 0; i < history.size(); i++) {
					if (history[i].getId() == id) {
						cout << "Enter Quantity: ";
						cin >> quantity;
						Item* it = &history[i];
						it->subQuantity(it->getQuantity());
						it->addQuantity(quantity);
						Stock::addItem(*it);
						found = true;
					}
				}
				
				if(found == false) {
				cout << "Error: ID not found" << endl;
				}

				do {
					cout << "Add another Item? [Y] -yes [N] - no :";
					cin >> yesno;
					if (yesno == "y" || yesno == "Y") {
						tf = true;
					}
					else if (yesno == "n" || yesno == "N") {
						tf = false;
					}
					else {
						cout << endl << "\"" << yesno << "\"" << " is not a valid option" << endl;
					}

				} while (!(yesno == "y" || yesno == "Y" || yesno == "n" || yesno == "N"));



			
			}




			}while (tf == true);
	
			Stock::display();
			noProducts = Stock::getSize();
	
	
	
	
	}












}