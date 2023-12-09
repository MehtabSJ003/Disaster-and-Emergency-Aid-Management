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
/*
Name - MEHTAB SINGH JAGDE
Student ID - 119003226
Email - mjagde@myseneca.ca
Section - ZEE
Date - 24 / 11 / 2023

We have completed this assignment ourselves respecting academic integrity.

*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#define _CRT_SECURE_NO_WARNINGS
#include "Utils.h"
#include <cstring>
#include <iomanip>
#include <string>
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
       bool check = false;
       if (prompt != nullptr)
       {
           cout << prompt;
       }
       do {
           userInput = getint();
           if (userInput >= min && userInput <= max)
           {
               check = true;
           }
           else
           {
               cout<< "Value out of range [" << min << "<=val<=" << max << "]: ";
           }
       } while (!check);
       return userInput;
   }
   double Utils::getdouble(const char* prompt, const char* errMes)
   {
       double userInput=0;
       if (prompt != nullptr)
       {
           cout << prompt;
       }
       do {
           cin >> userInput;
           if (!cin)
           {
               cout << "Invalid number, retry: ";
               cin.clear();
               cin.ignore(2000, '\n');
           }
       } while (!userInput);
       return userInput;
   }

   //Performs a foolproof entry of a double within a range.
   double Utils::getdouble(double min, double max, const char* prompt, const char* errMes)
   {
       double userInput=0;
       bool check = false;
       if (prompt != nullptr) 
       {
           do {
               userInput = getdouble(prompt, errMes);
               if (userInput >= min && userInput <= max)
               {
                   check = true;
               }
               else 
               {
                   cout << fixed << setprecision(2) << "Value out of range [" << min << "<=val<=" << max << "]:";
                   prompt = " ";
               }
           } while (!check);
       }
       return userInput;
   }
}