#include "stdafx.h"
#include "TimeParser.h"
#include "ParserHelperFunctions.h"
#include <sstream>

const vector<string> longDays = { "sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday" };
const vector<string> shortDays = { "sun", "mon", "tue", "wed", "thu", "fri", "sat" };

TimeParser::TimeParser()
{
}


TimeParser::~TimeParser()
{
}

struct tm * TimeParser::timeIterator(struct tm* day, int daysToAdd)
{
	day->tm_mday += daysToAdd;
	time_t next = mktime(day);
	struct tm * newDay = localtime(&next);

	return newDay;
}

int TimeParser::determineDaysToAdd(string day, bool isNextPresent)
{
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);
	int todayDayIndex = now->tm_wday;
	
	if (day == "today") {
		return 0;
	}
	else if (day == "tomorrow") {
		return 1;
	}
	else {
		int dayIndex = determineDayIndex(day);
		int toAdd = (dayIndex - todayDayIndex) % longDays.size();
		if (dayIndex = -1) {
			return -1;
		}
		if ((todayDayIndex < dayIndex) && isNextPresent)
			toAdd += 7;
		return toAdd;
	}
}

int TimeParser::determineDayIndex(string day)
{
	int index = -1;
	index = ParserHelperFunctions::findMatchingStringIndex(day, longDays);
	if (index = -1) {
		index = ParserHelperFunctions::findMatchingStringIndex(day, shortDays);
	}
	return index;
}

string TimeParser::printDate(struct tm* date)
{
	char buffer[80];
	strftime(buffer, 80, "%d/%m/%Y", date);
	string out = buffer;

	return out;
}

string TimeParser::parseDayOfWeek(string date)
{
	string dateToModify = date;
	bool isNext = false;
	dateToModify = ParserHelperFunctions::toLowerCaseString(dateToModify);
	if (dateToModify.substr(0, 5) == "next ") {
		isNext = true;
		dateToModify.erase(0, 5);
	}
	int toAdd = determineDaysToAdd(dateToModify, isNext);

	if (toAdd > -1) {
		time_t t = time(0);   // get time now
		struct tm * time = localtime(&t);
		time = timeIterator(time, toAdd);

		return printDate(time);
	}
	else {
		return date;
	}
}