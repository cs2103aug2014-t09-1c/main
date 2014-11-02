#pragma once
#ifndef PROGRAM_CONTROLLER
#define PROGRAM_CONTROLLER

#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include "ParsedDataDeployer.h"
#include "CommandAndArgumentParser.h"
#include "AddParser.h"
#include "DeleteParser.h"
#include "EditParser.h"
#include "SearchParser.h"
#include "ParsedDataPackage.h"


class ProgramController
{
private:
	fstream file;
	int displayCase = 0;
	string displayDate;
	vector<string> searchKeywords;
	string errorString;
	string fileName;
	string command;
	string arguments;
	ParsedDataPackage dataPackage;

	ParsedDataDeployer deployer;

public:
	ProgramController(string filename);
	~ProgramController();
	void executeEntry(string input);
	vector<string> populateSuggestionBox(string input);
	void executeSuggestionSelection(string selection, string lineText);
	vector<vector<string>> refreshTableDisplay();
	vector<vector<string>> displayTable(string date);
	string updateLineText(string inputText, bool isEnterPressed);
	void ConnectToCommandFeedback(string input);
	pair<int, int> getCompletedStatToday();
};

#endif
