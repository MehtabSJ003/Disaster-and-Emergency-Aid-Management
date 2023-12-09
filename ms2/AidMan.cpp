#define _CRT_SECURE_NO_WARNINGS
#include "AidMan.h"
#include "Utils.h"
/*
Name - MEHTAB SINGH JAGDE
Student ID - 119003226
Email - mjagde@myseneca.ca
Section - ZEE
Date - 15 / 11 / 2023

I have completed all my assignments myself respecting academic integrity.

*/
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;
namespace sdds {
	unsigned int AidMan::menu() const{
		cout << "Aid Management System" << endl;
		int currentYear, currentMonth, currentDay;
        //Getting current date
		ut.getSystemDate(&currentYear, &currentMonth, &currentDay);
		cout<<"Date: " << setfill('0') << setw(4) << currentYear << '/' << setw(2) << currentMonth << '/' << setw(2) << currentDay<<endl;
		cout << "Data file: " << (m_fileName ? m_fileName : "No file") << "\n\n";
        //running menu object
		return m_menuObject.run();
	}
	AidMan::AidMan(const char* fileName):m_menuObject("List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database"){
        if (fileName)
        {
            m_fileName = new char[strlen(fileName) + 1];
            strcpy(m_fileName, fileName);
        }
		else
		{
			m_fileName = nullptr;
		}
	}
	AidMan::~AidMan() {
		delete[] m_fileName;
        m_fileName = nullptr;
	}
	void AidMan::run() {
        int userInput;
        do {
            userInput = menu();
            switch (userInput) {
            case 1:
                cout << "\n****List Items****\n\n";
                break;
            case 2:
                cout << "\n****Add Item****\n\n";
                break;
            case 3:
                cout << "\n****Remove Item****\n\n";
                break;
            case 4:
                cout << "\n****Update Quantity****\n\n";
                break;
            case 5:
                cout << "\n****Sort****\n\n";
                break;
            case 6:
                cout << "\n****Ship Items****\n\n";
                break;
            case 7:
                cout << "\n****New/Open Aid Database****\n\n";
                break;
            }
        } while (userInput != 0);
        cout << "Exiting Program!" << endl;
	}
}