#pragma once
#ifndef ARRANGE_LOGIC
#define ARRANGE_LOGIC

#include <iostream>
#include <vector>
#include "FileLogic.h"
#include "TimeLogic.h"

using namespace std;

class ArrangeLogic
{
private:
	FileLogic fileHandler;

	TimeLogic getPriorityDateTime(string line);
	pair<vector<string>, vector<int>> addNonFloatEventToEntry(vector<string> lineEntry, vector<int> linePosition, int iteration);
	bool checkKeywordCriteria(string line, vector<string> keywords);

public:
	ArrangeLogic(FileLogic fileHandler);
	~ArrangeLogic();

	pair<vector<string>, vector<int>> getAllEntries();
	pair<vector<string>, vector<int>> getListOfEventsWithKeywords(vector<string> keywords);
	pair<vector<string>, vector<int>> getListOfEventsOnwardFrom(string date);
};

#endif

