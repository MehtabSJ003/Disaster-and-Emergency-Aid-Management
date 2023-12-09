/*
Name - MEHTAB SINGH JAGDE
Student ID - 119003226
Email - mjagde@myseneca.ca
Section - ZEE
Date - 02 / 12 / 2023

We have completed this assignment ourselves respecting academic integrity.

*/
#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include "Utils.h"
#include <iostream>
#include <cstring> 
using namespace std;
namespace sdds {
	Menu::Menu() {
		m_menu = nullptr;
		m_options = 0;
	}
	Menu::Menu(unsigned int option, const char* menu) {
		m_options = option;
		m_menu = nullptr;
		m_menu = new char[strlen(menu) + 1];
		strcpy(m_menu, menu);
	}
	Menu::~Menu() {
		delete[] m_menu;
		m_menu = nullptr;
	}
	unsigned int Menu::run()const {
		cout << m_menu << "0- Exit" << endl;
		int choice;
		choice = ut.getint(0, m_options, "> ", nullptr);
		return choice;
	}
}