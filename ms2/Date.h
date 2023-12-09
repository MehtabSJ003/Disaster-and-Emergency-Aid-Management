/*
Name - MEHTAB SINGH JAGDE
Student ID - 119003226
Email - mjagde@myseneca.ca
Section - ZEE
Date - 15 / 11 / 2023

I have completed all my assignments myself respecting academic integrity.

*/
#ifndef SDDS_DATE_H
#define SDDS_DATE_H
#include "Status.h"
#include <iostream>
namespace sdds{
	class Date {
		static const int maxYearValue = 2030;
		int m_year;
		int m_month;
		int m_day;
		Status m_state;
		bool m_formatted;
		bool validate();
		int UniqueDateValue()const;
	public:
		Date();
		Date(int year, int month, int day);
		bool operator==(const Date& src)const;
		bool operator!=(const Date& src)const;
		bool operator<(const Date& src)const;
		bool operator>(const Date& src)const;
		bool operator<=(const Date& src)const;
		bool operator>=(const Date& src)const;
		const Status& state();
		Date& formatted(bool format);
		operator bool()const;
		std::ostream& write(std::ostream& ostr)const;
		std::istream& read(std::istream& istr);
	};
	std::istream& operator>>(std::istream& istr,  Date& rhs);
	std::ostream& operator<<(std::ostream& ostr, const Date& rhs);
}
#endif