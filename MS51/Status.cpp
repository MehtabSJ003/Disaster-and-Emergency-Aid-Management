/*
Name - MEHTAB SINGH JAGDE
Student ID - 119003226
Email - mjagde@myseneca.ca
Section - ZEE
Date - 29 / 11 / 2023

We have completed this assignment ourselves respecting academic integrity.

*/
#define _CRT_SECURE_NO_WARNINGS
#include "Status.h"
#include "Utils.h"
#include <iostream>
#include <cstring>
namespace sdds {
	Status::Status() {
		m_description = nullptr;
		m_statusCode = 0;
	}
	Status::Status(const char* description) {
		m_description = nullptr;
		m_description = new char[strlen(description) + 1];
		strcpy(m_description, description);
		m_statusCode = 0;
	}
	Status::Status(int code) {
		m_description = nullptr;
		m_statusCode = code;
	}
	//Copy contructor
	Status::Status(const Status& src) {
		m_description = nullptr;
		m_statusCode = src.m_statusCode;
		if (src.m_description != nullptr)
		{
			m_description = new char[strlen(src.m_description) + 1];
			strcpy(m_description, src.m_description);
		}
		else
		{
			m_description = nullptr;
		}
	}
	Status::~Status() {
		clear();
	}
	//Copy assignment operator
	Status& Status::operator=(const Status& src) {
		if (this != &src)
		{
			delete[] m_description;
			m_description = nullptr;
			clear();
			m_statusCode = src.m_statusCode;
			if (src.m_description != nullptr)
			{
				m_description = new char[strlen(src.m_description) + 1];
				strcpy(m_description, src.m_description);
			}
		}
		return *this;
	}
	Status& Status::operator=(const char* description) {
		clear();
		if (description != nullptr)
		{
			m_description = new char[strlen(description) + 1];
			strcpy(m_description, description);
		}
		return *this;
	}
	Status& Status::operator=(int code) {
		clear();
		m_statusCode = code;
		return *this;
	}
	Status::operator int() const {
		return m_statusCode;
	}
	Status::operator const char* () const {
		return m_description;
	}
	Status::operator bool() const {
		bool check = false;
		if (m_description == nullptr && m_statusCode == 0)
		{
			check = true;
		}
		return check;
	}
	Status& Status::clear() {

		delete[] m_description;
		m_description = nullptr;
		m_statusCode = 0;

		return *this;
	}
	std::ostream& operator<<(std::ostream& ostr, const Status& rhs) {
		if (!rhs)
		{

			if (int(rhs) != 0)
			{
				ostr << "ERR#" << int(rhs) << ": ";
			}
			if (const char* description = rhs)
			{
				ostr << description;
			}
		}
		return ostr;
	}
}
