#pragma once
#ifndef PROGRAM_CONTROLLER
#define PROGRAM_CONTROLLER

#include <string>
#include <sstream>
#include <vector>
#include "ParsedDataDeployer.h"
#include "CommandAndArgumentParser.h"
#include "AddParser.h"
#include "DeleteParser.h"
#include "EditParser.h"
#include "ParsedDataPackage.h"
#include "FileLogic.h"


class ProgramController
{
private:
	int displayCase = 0;
	string displayDate;
	
	string fileName;
	string command;
	string arguments;
	ParsedDataPackage dataPackage;
	vector<ParsedDataPackage> dataPackages;

public:
	ProgramController(string filename);
	~ProgramController();
	void executeEntry(string input);
	vector<vector<string>> refreshTableDisplay();
	vector<vector<string>> displayTable(string date);
	void ConnectToCommandFeedback(string input);
	void ConnectToDoListOutput(vector<string> newLineEntry);
	void ConnectToDoListOutput(int position, string newLineEntry);
};

#endif
