/*
Name - MEHTAB SINGH JAGDE
Student ID - 119003226
Email - mjagde@myseneca.ca
Section - ZEE
Date - 03 / 12 / 2023

We have completed this assignment ourselves respecting academic integrity.

*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Perishable.h"
#include "AidMan.h"
#include "Date.h"
#include "Utils.h"
using namespace std;
namespace sdds {
	//Saving the file
	void AidMan::save() {
		if (m_fileName != nullptr)
		{
			ofstream file;
			file.open(m_fileName);
			for (int i = 0;i < m_iProductItems;i++)
			{
				m_iProduct[i]->save(file);
				//coming to newline to after printing one data
				file << endl;
			}
		}
	}
	//deleting the allocated memory
	void AidMan::deallocate() {
		if (m_iProductItems > 0)
		{
			for (int i = 0;i < m_iProductItems;i++)
			{
				delete m_iProduct[i];
				m_iProduct[i] = nullptr;
			}
			delete[] m_fileName;
			m_iProductItems = 0;
		}
	}
	//Loading the file
	bool AidMan::load() {
		int choice;
		int check = false;
		int count = 0;
		char firstChar;
		ifstream openFile(m_fileName);
		//If the file fails to open
		if (!openFile.is_open())
		{
			cout << "Failed to open " << m_fileName << " for reading!" << endl;
			cout << "Would you like to create a new data file?" << endl;
			cout << "1- Yes!" << endl;
			cout << "0- Exit" << endl;
			choice = ut.getint(0, 1, "> ", nullptr);
			if (choice == 1)
			{
				ofstream newDataFile(m_fileName);
			}
		}
		else
		{
			do
			{
				firstChar = openFile.peek();
				//The SKUs of perishable items starts with 1,2 or 3
				if (firstChar == '1' || firstChar == '2' || firstChar == '3')
				{
					m_iProduct[count] = new Perishable;
					if (m_iProduct[count] != nullptr)
					{
						m_iProduct[count]->load(openFile);
						if (m_iProduct[count])
						{
							check = true;
							m_iProductItems++;
							count++;
						}
						else
						{
							delete m_iProduct[count];
						}
					}
				}
				else if (firstChar == '4' || firstChar == '5' || firstChar == '6' || firstChar == '7' || firstChar == '8' || firstChar == '9')
				{
					m_iProduct[count] = new Item;
					if (m_iProduct[count] != nullptr)
					{
						m_iProduct[count]->load(openFile);
						if (m_iProduct[count])
						{
							check = true;
							m_iProductItems++;
							count++;
						}
						else
						{
							delete m_iProduct[count];
						}
					}
					openFile.ignore(2000, '\n');
				}
				else
				{
					openFile.setstate(ios::failbit);
					delete m_iProduct[count];
				}
			} while (!openFile.eof());
		}
		return check;
	}
	//Constructor
	AidMan::AidMan() {
		m_fileName = nullptr;
		m_iProductItems = 0;
		for (int i = 0;i < sdds_max_num_items;i++)
		{
			m_iProduct[i] = nullptr;
		}
	}
	//Header Menu
	unsigned int AidMan::menu() const {
		Date date;
		cout << "Aid Management System" << endl;
		cout << "Date: " << date << endl;
		if (m_fileName)
		{
			cout << "Data file: " << m_fileName << endl;
		}
		else
		{
			cout << "Data file: " << "No file" << endl;
		}
		cout << "---------------------------------" << endl;
		return m_menu.run();
	}
	//Displaying the list 
	int AidMan::list(const char* sub_desc) {
		ofstream file(m_fileName);
		int maxRecords = 0;
		if (m_iProductItems == 0)
		{
			cout << "The list is emtpy!" << endl;
		}
		else
		{
			cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
			if (sub_desc == nullptr)
			{
				for (int i = 0;i < m_iProductItems;i++)
				{
					m_iProduct[i]->linear(true);
					cout << "   " << i + 1;
					cout << " | " << *m_iProduct[i] << endl;
					maxRecords++;
				}
			}
			else
			{
				for (int i = 0;i < m_iProductItems;i++)
				{
					if (m_iProduct[i]->operator==(sub_desc))
					{
						m_iProduct[i]->linear(true);
						cout << "   " << i + 1;
						cout << " | " << *m_iProduct[i] << endl;
						maxRecords++;
					}
				}
			}
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
		}
		return maxRecords;
	}
	//Searches for the same SKUs
	int AidMan::search(int sku) const {
		//opening the file
		ifstream openFile(m_fileName);
		int index = 0;
		for (int i = 0;i < m_iProductItems;i++)
		{
			if (*m_iProduct[i] == sku)
			{
				//Assigning index to i
				index = i;
				i = m_iProductItems;
			}
			else
			{
				//IF sku is not matched index is set to -1
				index = -1;
			}
		}
		return index;
	}
	//Adds item(perishable or non-perishable) according to choice of user
	void AidMan::addItem() {
		int choice;
		int SKU;
		if (m_iProductItems >= sdds_max_num_items)
		{
			cout << "Database full!" << endl;
		}
		else
		{
			cout << "1- Perishable" << endl;
			cout << "2- Non-Perishable" << endl;
			cout << "-----------------" << endl;
			cout << "0- Exit" << endl;
			//Getting user's choice using utils function
			choice = ut.getint(0, 2, "> ", nullptr);
			if (choice == 0)
			{
				cout << "Aborted\n";
			}
			else
			{
				if (choice == 1)
				{
					m_iProduct[m_iProductItems] = new Perishable;
				}
				else if(choice==2)
				{
					m_iProduct[m_iProductItems] = new Item;
				}
				SKU = m_iProduct[m_iProductItems]->readSku(cin);
				//If the SKU does not match
				if (search(SKU) == -1)
				{
					m_iProduct[m_iProductItems]->read(cin);
					cout << endl;
					if (m_iProduct[m_iProductItems])
					{
						m_iProductItems++;
					}
					else
					{
						delete m_iProduct[m_iProductItems];
					}
				}
				else
				{
					cout << "Sku: " << SKU << " is already in the system, try updating quantity instead.\n";
					cout << endl;
					delete m_iProduct[m_iProductItems];
				}
			}
		}
	}
	//Removing the Item
	void AidMan::remove(int index) {
		delete m_iProduct[index];
		//Shifting the remaining products to fill the gap left by the removed product
		for (int i = 0;i < ((m_iProductItems - 1) - index);i++)
		{
			//Moving the product at index + (i + 1) to index + i
			m_iProduct[index + i] = m_iProduct[index + (i + 1)];
		}
		//Setting the last element to nullptr since it's a duplicate of the previous element
		m_iProduct[m_iProductItems - 1] = nullptr;
		m_iProductItems--;
	}
	//Asks for the specifications of the item to be removed
	void AidMan::removeItem() {
		char description[1000 + 1];
		int choice, index, SKU;
		cout << "Item description: ";
		cin >> description;
		if (list(description) > 0) 
		{ 
			SKU = ut.getint(10000, 99999, "Enter SKU: ", nullptr);
			index = search(SKU);
			if (index== -1)
			{
				//IF no SKU is found
				cout << "SKU not found!";
			}
			else 
			{ 
				cout << "Following item will be removed: " << endl;
				//displaying in non-linear form
				m_iProduct[index]->linear(false);
				m_iProduct[index]->display(cout);
				cout << endl;
				cout << "Are you sure?" << endl;
				cout << "1- Yes!" << endl;
				cout << "0- Exit" << endl;
				//calling the utils module function for the input
				choice= ut.getint(0, 1, "> ", nullptr);
				if (choice == 1)
				{
					remove(index);
					cout << "Item removed!" << endl;
					cout << endl;
				}
				else if(choice==2)
				{
					cout << "Aborted!" << endl;
					cout << endl;
				}
			}
		}
		
	}
	//Updating the Item
	void AidMan::update(int index) {
		int choice, remainingQuantity = 0, userInput;
		//Display menu options
		cout << "1- Add" << endl;
		cout << "2- Reduce" << endl;
		cout << "0- Exit" << endl;;
		//Getting user choice using the getint() function from ut object
		choice = ut.getint(0, 2, "> ", nullptr);
		switch (choice)
		{
		case 0:
			cout << "Aborted!" << endl;
			cout << endl;
			break;
		//Add
		case 1:
			//Calculating remaining quantity needed
			remainingQuantity = m_iProduct[index]->qtyNeeded() - m_iProduct[index]->qty();
			//Checking if there is a need to add more items
			if (remainingQuantity != 0) 
			{
				userInput = ut.getint(1, remainingQuantity, "Quantity to add: ", nullptr);
				//Adding the specified quantity to the product
				*m_iProduct[index] += userInput;
				cout << userInput << " items added!" << endl;
				cout << endl;
			}
			else 
			{
				//Display a message indicating that the quantity needed is already fulfilled
				cout << "Quantity Needed already fulfilled!" << endl;
				cout << endl;
			}
			break;
		//Reduce
		case 2:
			// Getting the current quantity on hand
			remainingQuantity = m_iProduct[index]->qty();
			//Checking if there are items to reduce
			if (remainingQuantity != 0) 
			{
				userInput = ut.getint(1, m_iProduct[index]->qty(), "Quantity to reduce: ", nullptr);
				//Reducing the specified quantity from the product
				*m_iProduct[index] -= userInput;
				cout << userInput << " items removed!" << endl;
				cout << endl;
			}
			else 
			{
				cout << "Quantity on hand is zero!" << endl;
				cout << endl;
			}
			break;
		}
	}
	//Asks for the specifications of the item to be updated
	void AidMan::updateQuantity() {
		char description[1000 + 1];
		int  index, SKU;
		cout << "Item description: ";
		//Getting description
		cin >> description;
		if (list(description) > 0)
		{
			//Getting SKU
			SKU = ut.getint(10000, 99999, "Enter SKU: ", nullptr);
			index = search(SKU);
			if (index == -1)
			{
				//IF no SKU is found
				cout << "SKU not found!";
			}
			else
			{
				//Calling the update function
				update(index);
			}
		}
	}
	//Implementing the functionality of menu
	void AidMan::run() {
		char fileName[100 + 1];
		char input;
		int row;
		unsigned int selection;
		do
		{
			selection = menu();
			if (selection != 0 && m_fileName == nullptr && selection != 7)
			{
				selection = 7;
			}
			switch (selection) {
			case 1:
				cout << endl << "****List Items****" << endl;
				list();
				cout << "Enter row number to display details or <ENTER> to continue:" << endl;
				cout << "> ";
				cin.ignore(2000, '\n');
				input = cin.get();
				if (input != '\n')
				{
					//converting character to integer explicitly
					row = input - '0';
					m_iProduct[row - 1]->linear(false);
					cout << *m_iProduct[row - 1] << endl;
				}
				else
				{
					cout << endl;
				}
				save();
				break;
			case 2:
				cout << endl << "****Add Item****" << endl;
				addItem();
				save();
				break;
			case 3:
				cout << endl << "****Remove Item****" << endl;
				//calling the remove function
				removeItem();
				//saving file
				save();
				break;
			case 4:
				cout << endl << "****Update Quantity****" << endl;
				//calling the update function
				updateQuantity();
				//saving the file
				save();
				break;
			case 5:
				cout << endl << "****Sort****" << endl;
				save();
				break;
			case 6:
				cout << endl << "****Ship Items****" << endl;
				save();
				break;
			case 7:
				cout << endl << "****New/Open Aid Database****" << endl;
				cout << "Enter file name: ";
				cin >> fileName;
				m_fileName = new char[strlen(fileName) + 1];
				strcpy(m_fileName, fileName);
				//loading the file
				load();
				cout << m_iProductItems << " records loaded!" << endl << endl;
				//saving file
				save();
				break;
			case 0:
				cout << "Exiting Program!" << endl;
				break;
			}
		} while (selection != 0);
	}
	AidMan::~AidMan() {
		delete[] m_fileName;
		m_fileName = nullptr;
		deallocate();
	}
}