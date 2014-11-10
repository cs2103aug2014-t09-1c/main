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
	/*
	* Checks if timed task is within searched date and time
	*/
	bool checkTimedTaskEligibility(string input, string line);
	/*
	* Determines how the search suggestion box will be ordered according
	* to keyword matches and diff costs by Levenshtein algorithm
	*/
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
	/*
	* Creates keywords and returns vector containing such that near matches input.
	*/
	vector<string> createKeywords(string input);
	/*
	* Responsible for finding the earliest free slot according to the duration and
	* free time present. Returns a pair of strings which contain date and duration
	* of earliest free slot.
	*/
	pair<string,string> getEarliestFreeSlot(map<string,string> fromToTime, map<string, int> duration);
	/*
	* Responsible for determining completion of today's task.. Returns a pair of 
	* integers which contain the number of completed tasks against 
	* tasks that should be done according to todayDate
	*/	
	pair<int, int> getTodayCompletionStat(string todayDate);

};

#endif

