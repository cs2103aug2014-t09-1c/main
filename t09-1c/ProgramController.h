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


#define WELCOME_MESSAGE \
	"Welcome. Please pick a command."
#define DISPLAY_ALL_CASE \
	-1
#define DISPLAY_HOME_CASE \
	0
#define DISPLAY_KEYWORD_CASE \
	1
#define HOME_COMMAND \
	"home"
#define ALL_COMMAND \
	"all"
#define ADD_COMMAND \
	"add"
#define ADD_APPEND \
	"add "
#define EDIT_COMMAND \
	"edit"
#define DELETE_COMMAND \
	"delete"
#define SEARCH_COMMAND \
	"search"
#define UNDO_COMMAND \
	"undo"
#define REDO_COMMAND \
	"redo"
#define COMPLETE_COMMAND \
	"complete"
#define UNCOMPLETE_COMMAND \
	"uncomplete"
#define SLOT_COMMAND \
	"slot"
#define CLIP_COMMAND \
	"clip"
#define SLOT_FORMAT \
	"slot [][][]"
#define ADD_FORMAT(name, date, time, category) \
	"add [" + name + "][" + date + "][" + time + "][" + category + "]"

class ProgramController
{
private:
	fstream file;
	bool isTestMode;

	string fileName;
	string displayDate;
	vector<string> searchKeywords;
	int displayCase = 0;
	
	string consoleString;
	
	string command;
	string arguments;
	ParsedDataPackage dataPackage;

	ParsedDataDeployer deployer;

public:
	ProgramController(string filename);
	ProgramController(vector<string> testVector);
	~ProgramController();

	void executeEntry(string input);
	vector<string> populateSuggestionBox(string input);
	void executeSuggestionSelection(string selection, string lineText);
	vector<vector<string>> refreshTableDisplay();
	vector<vector<string>> displayTable(string date);
	string updateLineText(string inputText, bool isEnterPressed);
	void ConnectToCommandFeedback(string input);
	pair<int, int> getCompletedStatToday();

	vector<string> returnTestVector();
	string getConsoleString();
	void clearConsoleString();
};

#endif
