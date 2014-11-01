#pragma once
#ifndef TIME_LOGIC
#define TIME_LOGIC

#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <ctime>
#include <iostream>
#include <list>

using namespace std;

class TimeLogic
{
private:
	bool timeFormatCheck = true;
	bool isPlusOne = false;

	string stringDate;
	string stringTime;
	int year, month, day, hour, min;
	
	//Set-Up TimeLogic Functions
	void convertStringToTimeLogic(string dateString, string timeString);
	void convertAndInsertDate(string date);
	void convertAndInsertTime(string time);
	bool isDateValid(int day, int mon, int year);
	bool isTimeValid(int hour, int min);
	void checkAndCorrectPlusOne();
	string addOneDay(string date);

public:
	TimeLogic(string date, string time); //time should be in "dd/mm/yyyy" & "HH:MM" format. NO EXCEPTIONS.
	~TimeLogic();
	bool getTimeFormatCheck();
	string returnPlusOne();
	string getStringDate();
	string getStringTime();
	void addHours(int hours, int mins);

	//These are functions which controller and logic can access staticlly
	static bool isFirstEarlierThanSecond(TimeLogic time1, TimeLogic time2);
	static bool isTimeBeforeToday(TimeLogic time1);
	static string getTimeNowInString();
};

#endif

