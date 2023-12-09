/*
Name - MEHTAB SINGH JAGDE
Student ID - 119003226
Email - mjagde@myseneca.ca
Section - ZEE
Date - 15 / 11 / 2023

I have completed all my assignments myself respecting academic integrity.

*/
#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include "Utils.h"
#include <iostream>
#include <cstring>
using namespace std;
namespace sdds {
	Menu::Menu(const char* menu):m_menu(nullptr),m_options(0){
		//Count Variable
		int count = 0;
		int length = strlen(menu);
		for (int i = 0; i < length; i++)
		{
			if (menu[i] == '\t') 
			{
				count++;
			}
		}
		if (menu && count <= maxOptions)
		{
			//Dynamic allocation
			m_menu = new char[strlen(menu) + 1];
			strcpy(m_menu, menu);
			m_options = ++count;
		}
		else 
        {
			delete[] m_menu;
			m_options = 0;
		}
	}
	Menu::~Menu() {
		delete[] m_menu;
		m_menu = nullptr;
	}
	unsigned int Menu::run()const {
		if (!m_menu)
		{
			cout << "Invalid Menu!" << endl;
			return 0;
		}
		else
		{
			// Display menu content in menu format
			for (int i = 1, j = 0; i <= m_options; i++) 
			{
				// Find the end of the option string
				int optionEnd = 0;
				while (m_menu[j + optionEnd] != '\t' && m_menu[j + optionEnd] != '\0') 
				{
					optionEnd++;
				}
				cout << i << "- " << string(m_menu + j, optionEnd) << endl;
				// Move to the next option
				j += optionEnd + 1;
			}
			cout << "---------------------------------" << endl;
			cout << "0- Exit" << endl;
			cout << "> ";
		    int userInput;
			//Taking user input till its valid
            while (!(cin >> userInput) || userInput < 0 || userInput>m_options)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				if (!userInput)
				{
					cout << "Invalid Integer, retry: ";
				}
				else if (userInput<0 || userInput>m_options)
				{
					cout << "Value out of range [0<=val<=" << m_options << "]: ";
				}
			}
			return userInput;
		}
	}
}