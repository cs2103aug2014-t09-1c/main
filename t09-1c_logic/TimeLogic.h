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
	/*
	* Checks Date Validity. NOTE THAT ANY YEAR BEFORE 2005 IS CONSIDERED INVALID.
	*/
	bool isDateValid(int day, int mon, int year);
	bool isTimeValid(int hour, int min);
	/*
	* Corrects date if the input time contains "+1"
	*/
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
	/*
	* Compares two Time Logics and returns if time 1 is earlier than time 2. Having same
	* time integers is considered earlier for time parsing reasons.
	*/
	static bool isFirstEarlierThanSecond(TimeLogic time1, TimeLogic time2);
	static bool isTimeBeforeNow(TimeLogic time1);
	static string getTimeNowInString();
};

#endif

