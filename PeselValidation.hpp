#pragma once
#include <string>
#include <iostream>
#include "Person.hpp"


bool isMonthValid(int month);
bool isLeapYear(int year);
bool isDayValid(int day, int maxDay);
int calculateMaxDay(int year, int month);
bool isDateValid(int year, int month, int day);
bool isChecksumValid(const std::string & pesel);
bool isPeselValid(const std::string pesel);
