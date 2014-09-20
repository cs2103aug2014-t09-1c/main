#pragma once
#include "stdafx.h"
#include <string>
#include <list>

using namespace std;

class ParsedDataPackage
{
public:
	ParsedDataPackage();
	~ParsedDataPackage();

	//all data related to event info to be stored are represented here.
	string event;
	int priority;
	int startHour;
	int startMin;
	int endHour;
	int endMin;
	int startDate;
	int StartMonth;
	int StartYear;
	int endDate;
	int endMonth;
	int endYear;
	list<string> keywords;

};

