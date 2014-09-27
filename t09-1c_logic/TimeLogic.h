#pragma once
#ifndef TIME_LOGIC
#define TIME_LOGIC

#include <time.h>
#include <iostream>

using namespace std;

class TimeLogic
{
private:
	int year, month, day, hour, min;
public:
	TimeLogic(string time); //time should be in "dd/mm/yy HH:MM" format. NO EXCEPTIONS.
	~TimeLogic();
	void declareTimeFormatError();
};

#endif

