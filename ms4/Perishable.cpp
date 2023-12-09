/*
Name - MEHTAB SINGH JAGDE
Student ID - 119003226
Email - mjagde@myseneca.ca
Section - ZEE
Date - 29 / 11 / 2023

We have completed this assignment ourselves respecting academic integrity.

*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include "Perishable.h"
#include "Utils.h"
using namespace std;
namespace sdds {
	//A Perishable object is created using the default constructor that creates an empty perishable item.
	Perishable::Perishable():Item() {
		m_handlingInstructions = nullptr;
	}
	//Copy constructor
	Perishable::Perishable(const Perishable& src) :Item(src) {
		m_handlingInstructions = nullptr;
		m_expiry = src.m_expiry;
		if (src.m_handlingInstructions != nullptr)
		{
			m_handlingInstructions = new char[strlen(src.m_handlingInstructions) + 1];
			strcpy(m_handlingInstructions, src.m_handlingInstructions);
		}
		else
		{
			m_handlingInstructions = nullptr;
		}
	}
	//Copy Assignment Operator
	Perishable& Perishable::operator=(const Perishable& src) {
		if (this != &src)
		{
			Item::operator=(src);
			delete[] m_handlingInstructions;
			m_expiry = src.m_expiry;
			if (src.m_handlingInstructions != nullptr)
			{
				m_handlingInstructions = new char[strlen(src.m_handlingInstructions) + 1];
				strcpy(m_handlingInstructions, src.m_handlingInstructions);
			}
			else
			{
				m_handlingInstructions = nullptr;
			}
		}
		return *this;
	}
	//Destructor
	Perishable::~Perishable() {
		delete[] m_handlingInstructions;
	}
	//returns a constant reference of the expiry date.
	const Date& Perishable::expiry() {
		return m_expiry;
	}
	//returns if sku is valid
	Perishable::operator bool() const {
		bool check = false;
		if ((m_SKU >= 10000 && m_SKU <= 39999) && m_state)
		{
			check = true;
		}
		return check;
	}
	//Override readSKU function
	int Perishable::readSku(std::istream& istr) {
		m_SKU = ut.getint(10000, 39999, "SKU: ", "Invalid Integer");
		return m_SKU;
	}
	//Override the save function
	ofstream& Perishable::save(ofstream& ofstr) const {
		Date d = m_expiry;
		d.formatted(false);
		if (m_state)
		{
			//Calling Item class save function
			Item::save(ofstr);
			ofstr << "\t";
			if (m_handlingInstructions != nullptr && strlen(m_handlingInstructions)>0)
			{
				ofstr << m_handlingInstructions;
			}
			ofstr << "\t";
			d.write(ofstr);
		}
		return ofstr;
	}
	//Override the load function
	ifstream& Perishable::load(ifstream& ifstr) {
		Item::load(ifstr);
		char handlingInstructions[1000 + 1];	
		delete[] m_handlingInstructions;
		m_handlingInstructions=nullptr;
		if (ifstr.peek() != EOF)
		{
			ifstr.ignore(2000, '\t');
			ifstr.getline(handlingInstructions, 1000 + 1,'\t');
			m_handlingInstructions = new char[strlen(handlingInstructions) + 1];
			strcpy(m_handlingInstructions, handlingInstructions);
			m_expiry.read(ifstr);
			ifstr.ignore();
			if (ifstr.fail())
			{
				m_state = "Input file stream read (perishable) failed!";
			}
		}
		else
		{
			ifstr.ignore(1);
		}
		return ifstr;
	}
	//Override the display function
	ostream& Perishable::display(ostream& ostr) const {
		Date d = m_expiry;
		//Setting the date format attribute to true
		d.formatted(true);
		if (m_SKU > 0)
		{
			if (m_state)
			{
				//Calling Item class linear function
				if (Item::linear())
				{
					//Calling Item class display function
					Item::display(ostr);
					if (m_handlingInstructions != nullptr && strlen(m_handlingInstructions) > 0)
					{
						ostr << "*";
					}
					else
					{
						ostr << ' ';
					}
					m_expiry.write(ostr);
				}
				else
				{
					ostr << "Perishable ";
					//Calling Item class display function
					Item::display(ostr);
					ostr << "Expiry date: ";
					d.write(ostr);
					ostr << endl;
					if (m_handlingInstructions != nullptr && strlen(m_handlingInstructions) > 0)
					{
						ostr << "Handling Instructions: " << m_handlingInstructions << endl;
					}
				}
			}
			else
			{
				ostr << m_state;
			}
		}
		return ostr;
	}
	//Override the read function
	istream& Perishable::read(istream& istr) {
		//+1 for the null terminator
		char handlingInstructions[1000 + 1];
		//Calling Item class read function
		Item::read(istr);
		delete[] m_handlingInstructions;
		m_handlingInstructions = nullptr;
		cout << "Expiry date (YYMMDD): ";
		m_expiry.read(istr);
		istr.ignore(2000, '\n');
		cout << "Handling Instructions, ENTER to skip: ";
		if (istr.peek() != '\n')
		{
			istr.getline(handlingInstructions, 1000 + 1);
			m_handlingInstructions = new char[strlen(handlingInstructions) + 1];
			strcpy(m_handlingInstructions, handlingInstructions);
		}
		if (istr.fail())
		{
			m_state = "Perishable console date entry failed!";
		}
		return istr;
	}
}