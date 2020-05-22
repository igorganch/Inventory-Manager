#include "Sold.h"

namespace sict {

	Sold::Sold() {

	}
	Sold::~Sold() {}

	void Sold::addSold(Item* it) {
		int index = Stock::find(it->getId());
		if (index > -1) {

			(*this)[index].addQuantity(it->getQuantity());


		}
		else {
			Stock::addItem(*it);
			
		}
		
	}
	void Sold::display() const {

		cout << endl << "===Sold Items History===" << endl;
		Stock::display();
		cout << "Profit - " ;
		cout << endl;
	}
	void Sold::findProfit() {
		int profit1 = 0;
		for (int i = 0; i < Stock::getSize(); i++) {
			profit1 += (*this)[i].getPrice();
		}
		profit = profit1;

	}





}