#pragma once
#ifndef SEARCH_LOGIC
#define SEARCH_LOGIC

#include "BaseClassLogic.h"
#include "DL_Algorithm.h"

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
	vector<string> keywords;
	vector<int> keywordPriority;

	int getSimilarityMatch(string keyword, string type, string entry);
	bool checkTimedTaskEligibility(string input, string line);
	void determinePriority(string keyword, int diffCost);

	void checkCategoryMatch(string input, string line);
	void checkNameMatch(string input, string line);
	void checkDateMatch(string input, string line);
	void checkEndTimeMatch(string input, string line);
	void checkTimedTaskMatch(string input, string line);
	void insertToKeywordVector(string input, string keyword, int diffCost);
	
public:
	
	SearchLogic(string fileName);
	SearchLogic(vector<string> testVector);
	~SearchLogic();
	vector<string> createKeywords(string input);
	pair<string,string> getEarliestFreeSlot(map<string,string> fromToTime, map<string, int> duration);
	pair<int, int> getTodayCompletionStat(string todayDate);

};

#endif

