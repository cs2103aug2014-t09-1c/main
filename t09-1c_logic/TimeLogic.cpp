#include "stdafx.h"
#include "TimeLogic.h"
#include <sstream>


TimeLogic::TimeLogic(string time)
{
	stringTime = time;
	convertStringToTimeLogic(stringTime);
}


TimeLogic::~TimeLogic()
{
}

bool TimeLogic::getTimeFormatCheck()
{
	return timeFormatCheck;
}

bool TimeLogic::isParameterStringEmpty(string parameter)
{
	return parameter.find_first_not_of(' ') == std::string::npos;
}

bool TimeLogic::isParameterStringANumber(string parameter)
{
	if (isParameterStringEmpty(parameter)) {
		return false;
	}
	else {
		return parameter.find_first_not_of("0123456789") == std::string::npos;
	}
}

int TimeLogic::convertStringToInt(string argument)
{
	if (isParameterStringANumber(argument)) {
		while (argument.substr(0, 1) == "0") {
			argument = argument.erase(0, 1);
		}
		int stringInInt = stoi(argument);
		return stringInInt;
	}
	else {
		return -1;
	}
}

void TimeLogic::convertStringToTimeLogic(string timeString)
{
	year = convertStringToYear(timeString.substr(YEAR_POSITION, YEAR_LENGTH_FORMAT));
	month = convertStringToMonth(timeString.substr(MONTH_POSITION, TIME_DATE_LENGTH_FORMAT));
	day = convertStringToDay(timeString.substr(DATE_POSITION, TIME_DATE_LENGTH_FORMAT));
	hour = convertStringToHour(timeString.substr(HOUR_POSITION, TIME_DATE_LENGTH_FORMAT));
	min = convertStringToMinutes(timeString.substr(MIN_POSITION, TIME_DATE_LENGTH_FORMAT));
}

int TimeLogic::convertStringToYear(string yearString)
{
	int year = convertStringToInt(yearString);
	if (year < 0) {
		timeFormatCheck = false;
	}
	return year;
}

int TimeLogic::convertStringToMonth(string monthString) 
{
	int month = convertStringToInt(monthString);
	if (month < 1 || month > MONTHS_IN_YEAR) {
		timeFormatCheck = false;
	}
	return month;
}

int TimeLogic::convertStringToDay(string dayString)
{
	int day = convertStringToInt(dayString);
	if (day < 0 || day > DAYS_IN_31MONTH) {
		timeFormatCheck = false;
	}
	if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (day > DAYS_IN_30MONTH) {
			timeFormatCheck = false;
		}
	}
	if (month == 2) {
		bool isLeap = 0;
		if ((year % 100 != 0 && year % 4 == 0) || (year % 100 == 0 && year % 400 == 0)) {
			isLeap = true;
			if (day > DAYS_IN_FEB_LEAP) {
				timeFormatCheck = false;
			}
		}
		if (!isLeap && day > DAYS_IN_FEB) {
			timeFormatCheck = false;
		}
	}
	
	return day;
}

int TimeLogic::convertStringToHour(string hourString)
{
	int hour = convertStringToInt(hourString);
	if (hour < 0 || hour > HOURS_IN_DAY) {
		timeFormatCheck = false;
	}
	return hour;
}

int TimeLogic::convertStringToMinutes(string minuteString)
{
	int minute = convertStringToInt(minuteString);
	if (minute < 0 || minute > MINUTES_IN_HOUR) {
		timeFormatCheck = false;
	}
	return minute;
}

void TimeLogic::declareTimeFormatError() 
{
	timeFormatCheck = false;
}

bool TimeLogic::isFirstEarlierThanSecond(TimeLogic time1, TimeLogic time2)
{
	bool boolStore = false;
	if (time1.getTimeFormatCheck() && time2.getTimeFormatCheck()) {
		int iterator = 0;
		int time1Vector[] = { time1.year, time1.month, time1.day, time1.hour, time1.min };
		int time2Vector[] = { time2.year, time2.month, time2.day, time2.hour, time2.min };
		while (iterator < 5) {
			iterator++;
			boolStore = (time1Vector[iterator] < time2Vector[iterator]);
		}
	}
	return boolStore;
}

bool TimeLogic::isTimeBeforeToday(TimeLogic time1)
{
	bool boolStore = false;
	if (time1.getTimeFormatCheck()) {
		int iterator = 0;
		time_t t = time(0);   // get time now
		struct tm * now = localtime(&t);
		int todayVector[] = { (now->tm_year + 1900), (now->tm_mon + 1), now->tm_mday};
		int time1Vector[] = { time1.year, time1.month, time1.day};
		while (iterator < 3) {
			iterator++;
			boolStore = (time1Vector[iterator] < todayVector[iterator]);
		}
	}
	return boolStore;
}