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
	int creationDate;
	int creationMonth;
	int creationYear;
	string catergory;
	int rating;
	string eventName;
	string type;
	int startHour;
	int startMin;
	int endHour;
	int endMin;
	int startDate;
	int startMonth;
	int startYear;
	int endDate;
	int endMonth;
	int endYear;
	list<string> keywords;
	bool completed;


};

