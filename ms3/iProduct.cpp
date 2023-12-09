/*
Name - MEHTAB SINGH JAGDE
Student ID - 119003226
Email - mjagde@myseneca.ca
Section - ZEE
Date - 24 / 11 / 2023

We have completed this assignment ourselves respecting academic integrity.

*/

#define _CRT_SECURE_NO_WARNINGS
#include "iProduct.h"
using namespace std;
namespace sdds {
	//Insertion operator overload
	ostream& operator<<(ostream& ostr, const iProduct& rhs) {
		rhs.display(ostr);
		return ostr;
	}
	//Extraction operator overload
	istream& operator>>(istream& istr, iProduct& rhs) {
		rhs.read(istr);
		return istr;
	}
}