#include "stdafx.h"
#include "TimeLogic.h"
#include <sstream>


TimeLogic::TimeLogic(string date, string time)
{
	stringDate = date;
	stringTime = time;
	convertStringToTimeLogic(stringDate, stringTime);
}


TimeLogic::~TimeLogic()
{
}

bool TimeLogic::getTimeFormatCheck()
{
	return timeFormatCheck;
}

void TimeLogic::convertStringToTimeLogic(string dateString, string timeString)
{
	if (timeString.size() == 5 && dateString.size() == 10) {
		convertAndInsertDate(dateString);
		if (isDateValid(day, month, year))
		{
			convertAndInsertTime(timeString);
			if (!isTimeValid(hour, min)) {
				timeFormatCheck = false;
			}
		}
		else {
			timeFormatCheck = false;
		}
	}
	else {
		timeFormatCheck = false;
	}
}
void TimeLogic::convertAndInsertDate(string date) 
{
	const char* str = date.c_str();
	sscanf(str, "%2d/%2d/%4d", &day, &month, &year);
}

void TimeLogic::convertAndInsertTime(string time)
{
	const char* str = time.c_str();
	sscanf(str, "%2d:%2d", &hour, &min);
}

bool TimeLogic::isDateValid(int day, int mon, int year)
{
	if (!(2005 <= year))
		return false;
	if (!(1 <= mon && mon <= 12))
		return false;
	if (!(1 <= day && day <= 31))
		return false;
	if ((day == 31) && (mon == 2 || mon == 4 || mon == 6 || mon == 9 || mon == 11))
		return false;
	if ((day == 30) && (mon == 2))
		return false;
	if ((mon == 2) && (day == 29) && (year % 4 != 0))
		return false;
	if ((mon == 2) && (day == 29) && (year % 400 == 0))
		return true;
	if ((mon == 2) && (day == 29) && (year % 100 == 0))
		return false;
	if ((mon == 2) && (day == 29) && (year % 4 == 0))
		return true;

	return true;
}

bool TimeLogic::isTimeValid(int hour, int min) 
{
	if (hour >= 24 || hour < 0) {
		return false;
	}
	if (min >= 60 || min < 0) {
		return false;
	}
	return true;
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
		int numberEqual = 0;
		int time1Vector[] = { time1.year, time1.month, time1.day, time1.hour, time1.min };
		int time2Vector[] = { time2.year, time2.month, time2.day, time2.hour, time2.min };
		while (iterator < 5) {

			if (!boolStore) {
				boolStore = (time1Vector[iterator] < time2Vector[iterator]);
				if (time1Vector[iterator] > time2Vector[iterator]) {
					break;
				}
			}
			bool isEqual = (time1Vector[iterator] == time2Vector[iterator]);
			if (isEqual) {
				numberEqual++;
			}
			iterator++;
		}
		if (numberEqual == 5) {
			boolStore = true;
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
			boolStore = (time1Vector[iterator] < todayVector[iterator]);
			if (boolStore) {
				break;
			}
			iterator++;
		}
	}
	return boolStore;
}

string TimeLogic::getTimeNowInString()
{
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);

	char buffer[80];
	strftime(buffer, 80, "%d/%m/%Y %H:%M", now);
	string out = buffer;

	return out;
}