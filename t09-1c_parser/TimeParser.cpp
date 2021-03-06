#include "stdafx.h"
#include "TimeParser.h"
#include <sstream>
#include <algorithm>

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
		int toAdd = ((dayIndex - todayDayIndex) + longDays.size()) % longDays.size();

		if (dayIndex == -1) {
			return -1;
		}

		if (toAdd == 0 ||((todayDayIndex <= dayIndex) && isNextPresent)) {
			toAdd += 7;
		}

		return toAdd;
	}
}

int TimeParser::determineDayIndex(string day)
{
	int index = -1;
	index = findMatchingStringIndex(day, longDays);

	if (index == -1) {
		index = findMatchingStringIndex(day, shortDays);
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
	dateToModify = toLowerCaseString(dateToModify);

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

string TimeParser::formatDate(string date)
{
	const int critical2DigitYear = 50;
	int inputYear = stoi(date.substr(4, 2));
	date.insert(2, "/");
	date.insert(5, "/");

	time_t t = time(0);   // get time now
	struct tm * time = localtime(&t);
	int year = time->tm_year + 1900;
	int addCentury = ((year - ((year / 100) * 100) > critical2DigitYear) && (year - ((year / 100) * 100) - critical2DigitYear) > inputYear) ? 1 : 0;
	string hundredsyear = to_string(year / 100 + addCentury);
	date.insert(6, hundredsyear);

	return date;
}

string TimeParser::toLowerCaseString(string input)
{
	transform(input.begin(), input.end(), input.begin(), ::tolower);

	return input;
}

int TimeParser::findMatchingStringIndex(string str, vector<string> lst)
{
	int index = -1;
	int lstSize = lst.size();

	for (int i = 0; i < lstSize; ++i) {
		if (lst[i] == str) {
			index = i;
			break;
		}
	}

	return index;
}
