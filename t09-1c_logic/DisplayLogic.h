#pragma once

#ifndef DISPLAY_LOGIC
#define DISPLAY_LOGIC

#include <iostream>
#include "FileLogic.h"
#include <vector>

#define DETAIL_AT_POS_0 \
	"name"
#define DETAIL_AT_POS_1 \
	"category"
#define DETAIL_AT_POS_2A \
	"date"
#define DETAIL_AT_POS_2B \
	"start"
#define DETAIL_AT_POS_3A \
	"date"
#define DETAIL_AT_POS_3B \
	"end"
#define DETAIL_AT_POS_4 \
	"complete"
#define NO_START_STRING \
	"In Progress"
#define FLOAT_START_STRING \
	"To Infinity"
#define FLOAT_END_STRING \
	"And Beyond"
#define TODAY \
	"Today, "

using namespace std;

class DisplayLogic
{
private:
	FileLogic fileHandler;
	vector<string> putToVectorEventDatails(string line, bool includeDate, string date);

public:
	DisplayLogic(string fileName);
	~DisplayLogic();

	vector<vector<string>> collectEventsOnDate(string date);
	vector<vector<string>> collectEventsFromDate(string date);
};

#endif 
