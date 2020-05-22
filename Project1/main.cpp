#include <iostream>
#include "item.h"
#include "Inventory.h"
#include "stock.h"
#include "Sold.h"
#include "Orders.h"
#include <vector>
#include <fstream>
#include <string>


using namespace std;
using namespace sict;




int displayMenu() {
	int ch;
	do {
		cout << endl;
		cout << "===Main Menu===" << endl;
		cout << " 1 - Inventory" << endl;
		cout << " 2 - Orders" << endl;
		cout << " 0 - Exit" << endl;
		cout << "Enter an option : ";
		cin >> ch;
		cout << endl;

		if (!(ch == 1 || ch == 2 || ch == 0)){
			cout << endl <<   "\"" << ch  << "\""<< " is not a valid option" << endl;
			
		}

	} while (!(ch == 1 || ch == 2 || ch == 0));

	return ch;
}
int displayOrderMenu() {
	int ch;
	do {
		cout << endl;
		cout << "===Orders===" << endl;
		cout << " 1 - Enter new Order" << endl;
		cout << " 2 - View Order status" << endl;
		cout << " 3 - Enter Delivered order" << endl;
		cout << " 0 - Exit" << endl;
		cout << "Enter an option : ";
		cin >> ch;
		cout << endl;

		if (!(ch == 1 || ch == 2 || ch ==3 ||ch == 0)) {
			cout << endl << "\"" << ch << "\"" << " is not a valid option" << endl;

		}

	} while (!(ch == 1 || ch == 2 || ch == 3 || ch == 0));

	return ch;




}
int displayInventory() {
	int ch2;
	do{
		cout << endl;
	cout << "====Inventory====" << endl;
	cout << " 1 - View Inventory" << endl;
	cout << " 2 - View sold items" << endl;
	cout << " 3 - Enter sold itmes" << endl;
	cout << " 4 - Add item" << endl;
	cout << " 0 - Return to main menu" << endl;
	cout << "Enter an option : ";
	cin >> ch2;
	cout << endl;

	if (!(ch2 == 1 || ch2 == 2 || ch2 == 3 || ch2 == 4 || ch2 == 0)){
		cout << endl << "\"" << ch2 << "\"" << " is not a valid option" << endl;
	}

	} while (!(ch2 == 1 || ch2 == 2 || ch2 == 3 || ch2 == 4 || ch2 == 0));

	return ch2;
}
int displayAddItem() {
	int ch3;
	do{
		cout << endl;
	cout << "===Add item===" << endl;
	cout << " 1 - Add existing item" << endl;
	cout << " 2 - Add new Item" << endl;
	cout << " 0 - Return" << endl;
	cout << "Enter an option : ";
	cin >> ch3;
	cout << endl;

	if (!(ch3 == 1 || ch3 == 2 || ch3 == 0)) {
		cout << endl << "\"" << ch3 << "\"" << " is not a valid option" << endl;
	}

} while (!(ch3 == 1 || ch3 == 2 || ch3 == 0));

return ch3;

}


int main(int argc, char** argv) {
	int ch;
	int ch2;
	int ch3;
	Inventory inv;
	Sold sold;
	vector<Orders*> order;
	
	std::fstream file(argv[1]);
	if (!file.is_open()) {
		std::cerr << "ERROR: Cannot open file [" << argv[1] << "].\n";
		return 1;
	}
	
	std::string line;

	do {
		getline(file, line);

		if (file) {
			if (line[0] != '#') {
				inv.loadStock(line);
			}
				
		
		}
	
	
	} while (file);
	file.close();
	std:: ifstream file1(argv[2]);
	if (!file1.is_open()) {
		std::cerr << "ERROR: Cannot open file [" << argv[2] << "].\n";
		return 1;
	}
	
	std::string line1;
	do {
		getline(file1, line1);
		

		if (file1) {
			if (line1[0] != '#') {
				sold.loadStock(line1);
			}


		}


	} while (file1);
	file1.close();

	std::ifstream file2(argv[3]);

	if (!file2.is_open()) {
		std::cerr << "ERROR: Cannot open file [" << argv[3] << "].\n";
		return 1;
	}

	do {
		getline(file2, line);

		if (file2) {
			if (line[0] != '#') {
				Orders* o1 = new Orders(line);
				
				order.push_back(o1);
				for (int i = 0; i < o1->getnoProducts(); i++) {
					getline(file2, line);
					o1->loadStock(line);
				}



			}


		}


	} while (file2);
	file2.close();

	do {
		
		ch = displayMenu();
		
		switch (ch) {
		case 1: //INVENTORY
			do {
				ch2 = displayInventory();
				
				if (ch2 == 1) { 
					inv.display();
				}
				else if (ch2 == 2) { // VIEW SOLD
					sold.display();
				}
				else if (ch2 == 3) {// MARK SOLD
				
					Item* it = inv.remove();
				if (it != nullptr) {
					sold.addSold(it);
					}
				}
				else if (ch2 == 4) { //ADD ITEM 
					do {
						ch3 = displayAddItem();

						if (ch3 == 1) { // ADD EXISITING ITEM
							inv.addqty();

						}
						else if (ch3 == 2) {  //ADD NEW ITEM
							int id;
							string name;
							int quantity;
							double price;
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
							inv.addItem(*it);



						}

					} while (ch3 != 0);



				}

			} while (ch2 != 0);
			break;
		case 2:	//Orders
			int ch4;
			do {
				 ch4 = displayOrderMenu();

				 if(ch4 ==1){ //enter new order
					 Orders* o1 = new Orders();;
					 o1->orderHistory(&inv);
					 o1->addOrder();
					 
					 order.push_back(o1);
				 
				 }
				 else if (ch4 == 2) { // View Order status
					 for (int i = 0; i < order.size(); i++) {
						 order[i]->displayOrder();
					 }
				 }
				 else if (ch4 == 3) {
					 bool found = false;
					 int id;

					 cout << "===Order List===" << endl;
					 for (int i = 0; i < order.size(); i++) {
						 order[i]->displayOrder();
					 }
					 do {
						 cout << endl << "Enter order id: ";
							 cin >> id;
							 for (int i = 0; i < order.size(); i++) {
							 if (id == order[i]->getId()){
								 found = true;
								 if (order[i]->getStatus() == true) {
									 cout << "Order has been already Delivered!" << endl;
								 }
								 else {
									 Item* items = order[i]->delivered();

									 inv.addOrders(items, order[i]->sold());
								 }
							 }
							}
							 if (found == false) {
								 cout << "Error: ID not found" << endl;
							 }
							 

					 } while (found == false);

					
				 }
			
			
			
			
			
			
			} while (ch4 != 0 );
			
		


			break;
		}
	} while (ch != 0);

	inv.exportStock(argv[1]);
	sold.exportStock(argv[2]);

	fstream ofs;
	ofs.open(argv[3], std::ofstream::out | std::ofstream::trunc);
	ofs << "#OrderId-----Status-----id-----Name-----Quantity-----Price" << endl;
	ofs.close();

	for (int i = 0; i < order.size(); i++) {
		order[i]->exportOrder(argv[3]);
	
	}









}