/*
Name - MEHTAB SINGH JAGDE
Student ID - 119003226
Email - mjagde@myseneca.ca
Section - ZEE
Date - 29 / 11 / 2023

We have completed this assignment ourselves respecting academic integrity.

*/
#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H
#include <iostream>
namespace sdds {
	class Status {
		char* m_description;
		int m_statusCode;
	public:
		Status();
		Status(const char* description);
		Status(int code);
		Status(const Status& src);
		~Status();
		Status& operator=(const Status& src);
		Status& operator=(const char* description);
		Status& operator=(int code);
		operator int() const;
		operator const char* () const;
		operator bool() const;
		Status& clear();
	};
	std::ostream& operator<<(std::ostream& ostr, const Status& rhs);
}
#endif