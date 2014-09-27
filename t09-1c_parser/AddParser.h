#pragma once
#include "BaseClassParser.h"
#include "ParsedDataPackage.h"
#include <string>

using namespace std;

// Syntax: -eventName- <startDate/startMonth/startYear> <startHour:startMin> <endDate/endMonth/endYear> <endHour:endMin> <Rating>

class AddParser :
	public BaseClassParser
{
private:
	string arguments;

public:
	AddParser();
	~AddParser();
	ParsedDataPackage parseAndReturn(string parseInput);

	void setArguments(string input);
	void extractEventName(string arguments);
};

