/*
Name - MEHTAB SINGH JAGDE
Student ID - 119003226
Email - mjagde@myseneca.ca
Section - ZEE
Date - 29 / 11 / 2023

We have completed this assignment ourselves respecting academic integrity.

*/
#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H
#include "iProduct.h"
#include "Status.h"
#include <iostream>
#include <fstream>
namespace sdds {
	class Item :public iProduct {
		double m_price;
		int m_quantity;
		int m_neededQuantity;
		char* m_description;
		bool m_flag;
	protected:
		Status m_state;
		int m_SKU;
	public:
		Item();
		Item(const Item& src);
		Item& operator=(const Item& src);
		~Item();
		virtual int qtyNeeded() const;
		virtual int qty() const;
		virtual operator double() const;
		virtual operator bool() const;
		virtual int operator-=(int qty);
		virtual int operator+=(int qty);
		virtual void linear(bool isLinear);
		virtual bool linear() const;
		void clear();
		virtual bool operator==(int sku) const;
		virtual bool operator==(const char* description) const;
		virtual std::ofstream& save(std::ofstream& ofstr) const;
		virtual std::ifstream& load(std::ifstream& ifstr);
		virtual std::ostream& display(std::ostream& ostr) const;
		virtual int readSku(std::istream& istr);
		virtual std::istream& read(std::istream& istr);
	};
}
#endif