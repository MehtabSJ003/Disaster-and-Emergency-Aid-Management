/*
Name - MEHTAB SINGH JAGDE
Student ID - 119003226
Email - mjagde@myseneca.ca
Section - ZEE
Date - 02 / 12 / 2023

We have completed this assignment ourselves respecting academic integrity.

*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include "Item.h"
#include "Utils.h"
using namespace std;
namespace sdds {
	//The Item has a default constructor that sets all the attributes to zero, nullptr and false.
	Item::Item() {
		m_price = 0.0;
		m_quantity = 0;
		m_neededQuantity = 0;
		m_description = nullptr;
		m_flag = false;
		m_SKU = 0;
	}
	//Copy Constructor
	Item::Item(const Item& src) {
		m_price = src.m_price;
		m_quantity = src.m_quantity;
		m_neededQuantity = src.m_neededQuantity;
		m_flag = src.m_flag;
		m_state = src.m_state;
		m_SKU = src.m_SKU;
		if (src.m_description != nullptr)
		{
			m_description = new char[strlen(src.m_description) + 1];
			strcpy(m_description, src.m_description);
		}
		else
		{
			m_description = nullptr;
		}
	}
	//Copy Assignment Operator
	Item& Item::operator=(const Item& src) {
		if (this != &src)
		{
			m_price = src.m_price;
			m_quantity = src.m_quantity;
			m_neededQuantity = src.m_neededQuantity;
			m_flag = src.m_flag;
			m_state = src.m_state;
			m_SKU = src.m_SKU;
			delete[] m_description;
			if (src.m_description != nullptr)
			{
				m_description = new char[strlen(src.m_description) + 1];
				strcpy(m_description, src.m_description);
			}
			else
			{
				m_description = nullptr;
			}
		}
		return *this;
	}
	//Destructor
	Item::~Item() {
		delete[] m_description;
	}
	//the qtyNeeded method returns the needed-quantity attribute
	int Item::qtyNeeded() const {
		return m_neededQuantity;
	}
	//the qty method returns the on-hand quantity attribute
	int Item::qty() const {
		return m_quantity;
	}
	//the double conversion operator overload returns the price
	Item::operator double() const {
		return m_price;
	}
	//the boolean conversion operator overload returns the state of the object being good.
	Item::operator bool() const {
		return m_state;
	}
	//the operator-= reduces the on-hand quantity by the received value
	int Item::operator-=(int qty) {
		if (qty > 0)
		{
			m_quantity -= qty;
		}
		return m_quantity;
	}
	//the operator+= increases the on-hand quantity by the received value
	int Item::operator+=(int qty) {
		if (qty > 0)
		{
			m_quantity += qty;
		}
		return m_quantity;
	}
	//the linear modifier sets the linear flag attribute to true or false.
	void Item::linear(bool isLinear) {
		m_flag = isLinear;
	}
	//Returns whether the Item is in linear or non-linear form
	bool Item::linear() const {
		return m_flag;
	}
	//resetting the state attribute.
	void Item::clear() {
		m_state.clear();
	}
	//the integer comparison returns true if the SKU attribute matches the received value
	bool Item::operator==(int sku) const {
		bool check = false;
		if (m_SKU == sku)
		{
			check = true;
		}
		return check;
	}
	//If any of the descriptions (The Items or the received value) are null or the match is not found, it will return false.
	bool Item::operator==(const char* description) const {
		bool check = false;
		if (strstr(m_description, description) != nullptr)
		{
			check = true;
		}
		if (m_description == nullptr || description == nullptr)
		{
			check = false;
		}
		return check;
	}
	//If the state of the Item is good, it will write SKU, description, on-hand quantity, needed quantity and price in tab-separated format.
	ofstream& Item::save(ofstream& ofstr) const {
		if (m_state)
		{
			ofstr << m_SKU << "\t" << m_description << "\t" << m_quantity << "\t" << m_neededQuantity << "\t" << fixed << setprecision(2) << m_price;
		}
		return ofstr;
	}
	//The tab-separated SKU, description, on-hand quantity, needed quantity and price are read into their corresponding attributes
	ifstream& Item::load(ifstream& ifstr) {
		delete[] m_description;
		m_description = nullptr;
		//+1 for the null terminator
		char description[1000 + 1];
		if (ifstr.peek() != EOF)
		{
			ifstr >> m_SKU;
			ifstr.ignore();
			//getting description upto 1000 characters
			ifstr.getline(description, 1000 + 1, '\t');
			m_description = new char[strlen(description) + 1];
			strcpy(m_description, description);
			ifstr >> m_quantity;
			ifstr >> m_neededQuantity;
			ifstr >> m_price;
			if (ifstr.fail())
			{
				m_state = "Input file stream read failed!";
			}
		}
		else
		{
			ifstr.ignore(1);
		}

		return ifstr;
	}
	//If the state is bad, the state is printed instead.
	ostream& Item::display(ostream& ostr) const {
		if (m_description != nullptr)
		{
			if (m_state)
			{
				if (m_flag)
				{
					ostr << setfill(' ');
					// Linear format
					ostr << setw(5) << m_SKU << " | ";
					if (strlen(m_description) <= 35)
					{
						ostr << left << setw(35) << m_description;
					}
					else
					{

						for (int i = 0; i < 35; i++)
						{
							ostr << m_description[i];
						}
					}
					ostr << " | " << right << setw(4) << m_quantity << " | " << setw(4) << m_neededQuantity << " | " << setw(7) << fixed << setprecision(2) << m_price << " |";
				}
				else
				{
					// Descriptive format
					ostr << "AMA Item:" << endl;
					ostr << m_SKU << ": " << m_description << endl;
					ostr << "Quantity Needed: " << m_neededQuantity << endl;
					ostr << "Quantity Available: " << m_quantity << endl;
					ostr << "Unit Price: $" << fixed << setprecision(2) << m_price << endl;
					ostr << "Needed Purchase Fund: $" << fixed << setprecision(2) << (m_neededQuantity - m_quantity) * m_price << endl;
				}
			}
			else
			{
				// Bad state
				ostr << m_state;
			}
		}
		return ostr;
	}
	// It makes sure the SKU number begins with digits 4 to 9 and it is 5 digits long.
	int Item::readSku(std::istream& istr) 
	{
		m_SKU = ut.getint(40000, 99999, "SKU: ", "Invalid Integer");
		return m_SKU;
	}
	//read will first prompt the user with the title "AMA Item" and then displays the SKU and reads the rest of the information in a foolproof way
	istream& Item::read(istream& istr) 
	{
		delete[] m_description;
		m_description = nullptr;
		istr.ignore(2000, '\n');
		//+1 for the null terminator
		char description[1000 + 1];
		cout << "AMA Item:" << endl;
		cout << "SKU: " << m_SKU << endl;
		cout << "Description: ";
		istr.getline(description, 1000 + 1);
		m_description = new char[strlen(description) + 1];
		strcpy(m_description, description);
		//Calling Utils module functions
		m_neededQuantity = ut.getint(1, 9999, "Quantity Needed: ", "Invalid Integer");
		m_quantity = ut.getint(0, m_neededQuantity, "Quantity On Hand: ", "Invalid Integer");
		m_price = ut.getdouble(0.00, 9999.00, "Unit Price: $", "Invalid number");
		if (istr.fail()) 
		{
			m_state = "Console entry failed!";
		}
		return istr;
	}
}