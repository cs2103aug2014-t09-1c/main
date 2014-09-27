#pragma once
#ifndef TIME_LOGIC
#define TIME_LOGIC

#include <time.h>
#include <ctime>
#include <iostream>
#include <list>

using namespace std;

class TimeLogic
{
private:
	bool timeFormatCheck = true;
	string stringTime;
	
	//Facts of life:
	const int TIME_DATE_LENGTH_FORMAT = 2;
	const int YEAR_LENGTH_FORMAT = 4;
	const int MONTHS_IN_YEAR = 12;
	const int DAYS_IN_31MONTH = 31;
	const int DAYS_IN_30MONTH = 30;
	const int DAYS_IN_FEB = 28;
	const int DAYS_IN_FEB_LEAP = 29;
	const int HOURS_IN_DAY = 24;
	const int MINUTES_IN_HOUR = 60;
	
	//indicates positioning in agreed format "dd/mm/yyyy HH:MM"
	const int DATE_POSITION = 0;
	const int MONTH_POSITION = 3;
	const int YEAR_POSITION = 6;
	const int HOUR_POSITION = 11;
	const int MIN_POSITION = 14;
	
	//Set-Up TimeLogic Functions
	void convertStringToTimeLogic(string timeString);
	bool isParameterStringEmpty(string parameter);
	bool isParameterStringANumber(string parameter);
	int convertStringToInt(string argument);
	int convertStringToYear(string yearString);
	int convertStringToMonth(string monthString);
	int convertStringToDay(string dayString);
	int convertStringToHour(string hourString);
	int convertStringToMinutes(string minuteString);

public:
	int year, month, day, hour, min;
	TimeLogic(string time); //time should be in "dd/mm/yyyy HH:MM" format. NO EXCEPTIONS.
	~TimeLogic();
	bool getTimeFormatCheck();
	void declareTimeFormatError();

	//These are functions which controller and logic can access staticlly
	static bool isFirstEarlierThanSecond(TimeLogic time1, TimeLogic time2);
	static bool isTimeBeforeToday(TimeLogic time1);
	static string getTimeNowInString();
	static 
};

#endif

