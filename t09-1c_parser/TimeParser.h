#pragma once
#ifndef TIME_PARSER
#define TIME_PARSER

#include <iostream>
#include <list>
#include "time.h"

using namespace std;

class TimeParser
{
private:
	const list<string> longDays = { "sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday" };
	const list<string> shortDays = { "sun", "mon", "tue", "wed", "thu", "fri", "sat" };

protected:

	TimeParser();
	~TimeParser();

public:
	static string parseDayOfWeek(string date); //Enter days of week shown above, "today" or "tomorrow", return day in dd/mm/yyyy format
};
#endif
