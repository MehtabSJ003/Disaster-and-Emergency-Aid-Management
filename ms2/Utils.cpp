/***********************************************************************
// Final project Milestone 1
// Module: Utils
// File: Utils.h
// Version 1.0
// Author  Fardad Soleimanloo
// Description
//
// Revision History
// -----------------------------------------------------------
// Name                 Date            Reason
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
/*
Name - MEHTAB SINGH JAGDE
Student ID - 119003226
Email - mjagde@myseneca.ca
Section - ZEE
Date - 15 / 11 / 2023

I have completed all my assignments myself respecting academic integrity.

*/
#define _CRT_SECURE_NO_WARNINGS
#include "Utils.h"
#include <cstring>
using namespace std;
namespace sdds {
   Utils ut;
   void Utils::testMode(bool testmode) {
      m_testMode = testmode;
   } 
   void Utils::getSystemDate(int* year, int* mon, int* day) {
      if (m_testMode) {
         if(day) *day = sdds_testDay;
         if(mon) *mon = sdds_testMon;
         if(year) *year = sdds_testYear;
      }
      else {  
         time_t t = std::time(NULL);
         tm lt = *localtime(&t);
         if (day) *day = lt.tm_mday;
         if (mon) *mon = lt.tm_mon + 1;
         if (year) *year = lt.tm_year + 1900;
      }
   }
   int Utils::daysOfMon(int month, int year)const {
      int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
      int mon = (month >= 1 && month <= 12 ? month : 13)-1;
      return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
   }
   void Utils::alocpy(char*& destination, const char* source) {
       delete[] destination;
       destination = nullptr;
       if (source != nullptr)
       {
           destination = new char[strlen(source) + 1];
           strcpy(destination, source);
       }
   }
   int Utils::getint(const char* prompt) {
       int userInput;
       if (prompt != nullptr)
       {
           cout << prompt;
       }
       do {
           cin >> userInput;
           if (!cin)
           {
               cout << "Invalid Integer, retry: ";
               cin.clear();
               cin.ignore(2000, '\n');
           }
       } while (!userInput);
       return userInput;
   }
   int Utils::getint(int min, int max, const char* prompt, const char* errMes) {
       int userInput;
       if (prompt != nullptr)
       {
           cout << prompt;
       }
       do {
           userInput = getint();
           if (userInput >= min && userInput <= max)
           {
               break;
           }
           if (errMes != nullptr)
           {
               cout<<errMes<< ", retry: ";
           }
           else
           {
               cout<< "Value out of range [" << min << "<=val<=" << max << "], retry: ";
           }
       } while (!userInput);
       return userInput;
   }
}