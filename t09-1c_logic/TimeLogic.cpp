#include "stdafx.h"
#include "TimeLogic.h"
#include <sstream>


TimeLogic::TimeLogic(string date, string time)
{
	stringDate = date;
	stringTime = time;
	checkAndCorrectPlusOne();
	convertStringToTimeLogic(stringDate, stringTime);
}


TimeLogic::~TimeLogic()
{
}

bool TimeLogic::getTimeFormatCheck()
{
	return timeFormatCheck;
}

string TimeLogic::returnPlusOne()
{
	string plusOne;
	if (isPlusOne) {
		plusOne = "+1";
	}
	return plusOne;
}

string TimeLogic::getStringDate()
{
	return stringDate;
}

string TimeLogic::getStringTime()
{
	return stringTime;
}

void TimeLogic::checkAndCorrectPlusOne()
{
	if (stringTime.size() == 7 && stringTime.substr(5, 2) == "+1") {
		stringTime = stringTime.substr(0, 5);
		stringDate = addOneDay(stringDate);
		isPlusOne = true;
	}
}

string TimeLogic::addOneDay(string date)
{
	const char* str = date.c_str();
	int tempYear, tempMonth, tempDay;
	sscanf(str, "%2d/%2d/%4d", &tempDay, &tempMonth, &tempYear);
	if (isDateValid(tempDay, tempMonth, tempYear)) {
		time_t t = time(0);
		struct tm * now = localtime(&t);
		now->tm_year = tempYear - 1900;
		now->tm_mon = tempMonth - 1;
		now->tm_mday = tempDay + 1;
		time_t nextDay = mktime(now);
		struct tm * newDay = localtime(&nextDay);
		char buffer[80];
		strftime(buffer, 80, "%d/%m/%Y", newDay);
		string newDate = buffer;
		return buffer;
	}
	return date;
}

void TimeLogic::addHours(int hours, int mins)
{
	if (hours <= 23 && mins <= 59) {
		string oldDate = stringDate;
		if (getTimeFormatCheck()) {
			time_t t = time(0);
			struct tm * now = localtime(&t);
			now->tm_year = year - 1900;
			now->tm_mon = month - 1;
			now->tm_mday = day;
			now->tm_hour = hour + hours;
			now->tm_min = min + mins;
			time_t newTime = mktime(now);
			struct tm * newTm = localtime(&newTime);
			char newDt[80];
			strftime(newDt, 80, "%d/%m/%Y", newTm);
			string newDate = newDt;
			if ((newDate != oldDate && !isPlusOne) || newDate == oldDate) {
				if (newDate != oldDate) {
					isPlusOne = true;
				}
				stringDate = newDate;
				char newHHMM[80];
				strftime(newHHMM, 80, "%H:%M", newTm);
				string newTime = newHHMM;
				stringTime = newTime;
				convertStringToTimeLogic(stringDate, stringTime);
			}
		}
	}
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