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
			ofstream file(m_fileName);
			for (int i = 0;i < m_iProductItems;i++)
			{
				m_iProduct[i]->save(file);
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
		char input;
		int row;
		if (m_iProductItems == 0)
		{
			cout << "The list is emtpy!" << endl;
		}
		else
		{
			if (sub_desc == nullptr)
			{
				for (int i = 0;i < m_iProductItems;i++)
				{
					m_iProduct[i]->linear(true);
				}
			}
			else
			{
				for (int i = 0;i < m_iProductItems;i++)
				{
					if (m_iProduct[i]->operator==(sub_desc))
					{
						cout << m_iProduct[i];
					}
				}
			}
			cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
			for (int i = 0;i < m_iProductItems;i++)
			{
				cout << "   " << i + 1;
				cout << " | " << *m_iProduct[i] << endl;
			}
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
			cout << "Enter row number to display details or <ENTER> to continue:" << endl;
			cout << "> ";
			cin.ignore(2000, '\n');
			input = cin.get();
			if (input != '\n')
			{
				row = input - '0';
				m_iProduct[row - 1]->linear(false);
				cout << *m_iProduct[row - 1] << endl;
			}
		}
		cout << endl;
		return m_iProductItems;
	}
	//Implementing the functionality of menu
	void AidMan::run() {
		char fileName[100 + 1];
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
				break;
			case 2:
				cout << endl << "****Add Item****" << endl << endl;
				break;
			case 3:
				cout << endl << "****Remove Item****" << endl << endl;
				break;
			case 4:
				cout << endl << "****Update Quantity****" << endl << endl;
				break;
			case 5:
				cout << endl << "****Sort****" << endl << endl;
				break;
			case 6:
				cout << endl << "****Ship Items****" << endl << endl;
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