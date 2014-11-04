#pragma once
#ifndef PARSE_DATA_DEPLOYER
#define PARSE_DATA_DEPLOYER

#include "ParsedDataPackage.h"

class ParsedDataDeployer
{
private:
	string consoleString;
	string fileName = "";

	vector<string> testVectorStore;
	bool isTestMode = false;

public:
	ParsedDataDeployer(string fileName);
	ParsedDataDeployer(vector<string> testVector);
	~ParsedDataDeployer();
	void executeAdd(ParsedDataPackage addPackage);
	void executeDelete(ParsedDataPackage deletePackage, string date, vector<string> keywords, int displayCase);
	void executeEdit(ParsedDataPackage editPackage, string date, vector<string> keywords, int displayCase);
	vector<string> executeSearch(string fileName);
	void executeUndo();
	void executeRedo();
	void executeComplete(ParsedDataPackage completePackage, string date, vector<string> keywords, int displayCase);
	void executeUncomplete(ParsedDataPackage uncompletePackage, string date, vector<string> keywords, int displayCase);
	vector<vector<string>> getDisplayEvents(string date, vector<string> keywords, int displayCase);
	
	string executeFormatContentsToLineEdit(int position, string date, vector<string> keywords, int displayCase);
	pair <string, string> executeGetEarliestFreeSlot(ParsedDataPackage freeSlotPackage);
	pair<int, int> executeGetTodayCompletionStat(string todayDate);
	string returnConsoleString();

	vector<string> returnTestVector();
};
#endif