#pragma once
#ifndef SEARCH_LOGIC
#define SEARCH_LOGIC

#include "BaseClassLogic.h"
#include <string>
#include <iostream>
#include <vector>

#define SUGGESTIONS_LIMIT \
	20
#define MIMUMUM_LENGTH \
	2
#define NONDATETIMEMAXCOST \
	10
#define DATETIMEMAXCOST \
	0

class SearchLogic :
	public BaseClassLogic
{

private:

	FileLogic fileHandler;

	int getSimilarityMatch(string keyword, string type, string entry);
	bool checkTimedTaskEligibility(string input, string line);
	pair<vector<string>, vector<int>> determinePriority(vector<string> list, vector<int> priority, string keyword, int diffCost);

public:
	
	SearchLogic(string fileName);
	~SearchLogic();
	vector<string> createKeywords(string input);
	vector<string> getFreeSlots(string date);
	

};

#endif

