/*
Name - MEHTAB SINGH JAGDE
Student ID - 119003226
Email - mjagde@myseneca.ca
Section - ZEE
Date - 29 / 11 / 2023

We have completed this assignment ourselves respecting academic integrity.

*/
#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H
#include <iostream>
#include <fstream>
#include "Item.h"
#include "Date.h"
namespace sdds {
	class Perishable :public Item {
		Date m_expiry;
		char* m_handlingInstructions;
	public:
		Perishable();
		Perishable(const Perishable& src);
		Perishable& operator=(const Perishable& src);
		~Perishable();
		const Date& expiry();
		operator bool() const;
		int readSku(std::istream& istr);
		std::ofstream& save(std::ofstream& ofstr) const;
		std::ifstream& load(std::ifstream& ifstr);
		std::ostream& display(std::ostream& ostr) const;
		std::istream& read(std::istream& istr);
	};
}
#endif