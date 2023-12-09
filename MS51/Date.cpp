/*
Name - MEHTAB SINGH JAGDE
Student ID - 119003226
Email - mjagde@myseneca.ca
Section - ZEE
Date - 02 / 12 / 2023

We have completed this assignment ourselves respecting academic integrity.

*/
#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"
#include "Utils.h"
#include <iomanip>
#include <string>
using namespace std;
namespace sdds {
	//Checks if the date is valid
	bool Date::validate() {
		bool check = true;
		int currentYear;
		ut.getSystemDate(&currentYear);
		if (m_year<currentYear || m_year>maxYearValue)
		{
			m_state = "Invalid year in date";
			m_state = 1;
			check = false;
		}
		else if (m_month < 1 || m_month>12)
		{
			m_state = "Invalid month in date";
			m_state = 2;
			check = false;
		}
		else if (m_day<1 || m_day>ut.daysOfMon(m_month, m_year))
		{ 
			m_state = "Invalid day in date";
			m_state = 3;
			check = false;
		} 
		if (check)
		{
			m_state.clear();
		}
		return check;
	}
    //returns a unique date value
	int Date::UniqueDateValue()const {
		return (m_year * 372) + (m_month * 31) + m_day;
	}
	Date::Date() {
		m_formatted = true;
		ut.getSystemDate(&m_year, &m_month, &m_day);
	}
	Date::Date(int year, int month, int day) {
		m_year = year;
		m_month = month;
		m_day = day;
		m_formatted = true;
		validate();
	}
    Date::Date(const Date& src) {
		m_year = src.m_year;
		m_month = src.m_month;
		m_day = src.m_day;
		m_state = src.m_state;
		m_formatted = src.m_formatted;
	}
    Date& Date::operator=(const Date& src) {
		if (this != &src)
		{
			m_year = src.m_year;
			m_month = src.m_month;
			m_day = src.m_day;
			m_state = src.m_state;
			m_formatted = src.m_formatted;
		}
		return *this;
	}
	bool Date::operator==(const Date& src)const {
		bool check = false;
		if (UniqueDateValue() == src.UniqueDateValue())
		{
			check = true;
		}
		return check;
	}
	bool Date::operator!=(const Date& src)const {
		bool check = false;
		if (UniqueDateValue() != src.UniqueDateValue())
		{
			check = true;
		}
		return check;
	}
	bool Date::operator<(const Date& src)const {
		bool check = false;
		if (UniqueDateValue() < src.UniqueDateValue())
		{
			check = true;
		}
		return check;
	}
	bool Date::operator>(const Date& src)const {
		bool check = false;
		if (UniqueDateValue() > src.UniqueDateValue())
		{
			check = true;
		}
		return check;
	}
	bool Date::operator<=(const Date& src)const {
		bool check = false;
		if (UniqueDateValue() <= src.UniqueDateValue())
		{
			check = true;
		}
		return check;
	}
	bool Date::operator>=(const Date& src)const {
		bool check = false;
		if (UniqueDateValue() >= src.UniqueDateValue())
		{
			check = true;
		}
		return check;
	}
	const Status& Date::state() {
		return m_state;
	}
	Date& Date::formatted(bool format) {
		m_formatted = format;
		return *this;
	}
	//Returns state of the object
	Date::operator bool()const {
		return m_state;
	}
	//Formats the date according to m_formatted attribute
	ostream& Date::write(ostream& ostr)const {
		if (m_formatted)
		{
			ostr << setfill('0') << setw(4) << m_year << '/' << setw(2) << m_month << '/' << setw(2) << m_day;
		}
		else
		{
			ostr << setfill('0') << setw(2) << m_year % 100 << setw(2) << m_month << setw(2) << m_day;
		}
		return ostr;
	}
	//Reads the date inputed by user
	istream& Date::read(istream& istr) {
		delete[] m_state;
		int inputDate;
		istr >> inputDate;
		//duplicate input value
		int countDate = inputDate;
		//count variable
		int count = 0;
		int currentYear, currentMonth, currentDay;
		ut.getSystemDate(&currentYear, &currentMonth, &currentDay);
		if (!inputDate)
		{
			m_state = "Invalid date value";
		}
		else
		{
			//COunting the number of digits entered by the user
			while (countDate != 0)
			{
				count++;
				countDate /= 10;
			}
			if (count == 4)
			{
				m_year = currentYear;
				m_month = inputDate / 100;
				m_day = inputDate % 100;
			}
			else if(count==6)
			{
				int date = inputDate % 10000;
				m_year = inputDate / 10000;
				if (m_year != 0)
				{
					//converting year into string to add the prefix '20' for validating it
					string yearString = to_string(m_year);
					yearString = to_string(currentYear / 100) + yearString;
					int yearInteger = std::stoi(yearString);
					m_year = yearInteger;
				}
				m_month = date / 100;
				m_day = date % 100;
			}
			else if(count==2)
			{
				m_month = inputDate / 100;
			}
			if (!validate())
			{
				istr.setstate(ios::badbit);
			}
		}
		return istr;
	}
	istream& operator>>(istream& istr, Date& rhs) {
		rhs.read(istr);
		return istr;
	}
	ostream& operator<<(ostream& ostr,const Date& rhs) {
		rhs.write(ostr);
		return ostr;
	}

}