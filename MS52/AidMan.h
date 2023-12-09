/*
Name - MEHTAB SINGH JAGDE
Student ID - 119003226
Email - mjagde@myseneca.ca
Section - ZEE
Date - 02 / 12 / 2023

We have completed this assignment ourselves respecting academic integrity.

*/
#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H
#include "iProduct.h"
#include "Menu.h"
namespace sdds {
	const int sdds_max_num_items = 100;
	class AidMan {
		iProduct* m_iProduct[sdds_max_num_items];
		int m_iProductItems;
		char* m_fileName;
		Menu m_menu = { 7,"1- List Items\n"
								"2- Add Item\n"
								"3- Remove Item\n"
								"4- Update Quantity\n"
								"5- Sort\n"
								"6- Ship Items\n"
								"7- New/Open Aid Database\n"
								"---------------------------------\n" };

		void save();
		void deallocate();
		bool load();
	public:
		AidMan();
		unsigned int menu() const;
		int list(const char* sub_desc = nullptr);
		int search(int sku) const;
		void addItem();
		void run();
		~AidMan();
	};
}
#endif