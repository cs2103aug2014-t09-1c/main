#include "stdafx.h"
#include "AddParser.h"

// Syntax: [eventName] <startDate/startMonth/startYear> <startHour:startMin> <endDate/endMonth/endYear> <endHour:endMin> <Rating>

AddParser::AddParser()
{
}


AddParser::~AddParser()
{
}

void AddParser::setArguments(string input)
{
	arguments = input;
}

void AddParser::extractEventName(string arguments)
{
	string eventName;
	
}