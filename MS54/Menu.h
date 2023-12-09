/*
Name - MEHTAB SINGH JAGDE
Student ID - 119003226
Email - mjagde@myseneca.ca
Section - ZEE
Date - 02 / 12 / 2023

We have completed this assignment ourselves respecting academic integrity.

*/
#ifndef SDDS_MENU_H
#define SDDS_MENU_H
namespace sdds {
	class Menu {
		//constant integer
		static const int maxOptions = 15;
		char* m_menu;
		int m_options; 
	public:
		Menu();
		Menu(unsigned int option, const char* menu);
		Menu(const Menu& src) = delete;
		Menu& operator=(const Menu& src) = delete;
		~Menu();
		unsigned int run()const;
	};
}
#endif