#pragma once
#ifndef TIME_PARSER
#define TIME_PARSER

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include "time.h"

using namespace std;

class TimeParser
{
private:
	static struct tm * timeIterator(struct tm* day, int daysToAdd);
	static int determineDaysToAdd(string day, bool isNextPresent);
	static string printDate(struct tm* date);
	static int determineDayIndex(string day);
	static string toLowerCaseString(string input);
	static int findMatchingStringIndex(string str, vector<string> lst);

protected:
	TimeParser();
	~TimeParser();

public:
	static string parseDayOfWeek(string date); 
	//Enter days of week shown above, "today" or "tomorrow", return day in dd/mm/yyyy format.
	//If next is Present i.e. "next Thursday", date will be that of one week later.
	//If format error (including that of using dd/mm/yyyy), whole string entered is returned.
	static string formatDate(string date);
	//ddmmyy to dd/mm/yyyy

};
#endif
