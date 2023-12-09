/*
Name - MEHTAB SINGH JAGDE
Student ID - 119003226
Email - mjagde@myseneca.ca
Section - ZEE
Date - 15 / 11 / 2023

I have completed all my assignments myself respecting academic integrity.

*/
#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H
#include "Menu.h"
namespace sdds {
	class AidMan {
		char* m_fileName;
		Menu m_menuObject;
		unsigned int menu() const;
	public:
		AidMan(const char* fileName);
		AidMan(const AidMan& src) = delete;
		AidMan& operator=(const AidMan& src) = delete;
		~AidMan();
		void run();
	};
}
#endif
