#include "stdafx.h"
#include "ProgramController.h"
#include "ParsedDataDeployer.h"
#include "ParsedDataPackage.h"
#include <vector>
#include "DisplayLogic.h"
#include "TimeParser.h"
#include "CompleteParser.h"
#include "SearchLogic.h"

//after an input is scanned by UI method, call to method sendToParse is made to send input to Parser
//after Parser returns the variables in ParsedDataPackage, send the details to logic
//after file output returns an output, controller sends it to UI

ProgramController::ProgramController(string fileName) : deployer(fileName)
{
	this->fileName = fileName;
	file.open(fileName, ios::out | ios::app);
	file << "";
	displayDate = TimeParser::parseDayOfWeek("today");
}


ProgramController::~ProgramController()
{
	file.close();
}

void ProgramController::executeEntry(string input)//placeholder input for scanned input from UI
{
	CommandAndArgumentParser inputParse(input);

	command = inputParse.command;
	arguments = inputParse.arguments;

	try {
		if (command == "home") {
			displayCase = 0;
			searchKeywords.clear();
		}
		else if (command == "all") {
			displayCase = -1;
			searchKeywords.clear();
		}
		else if (command == "add") {
			AddParser addParsing;
			BaseClassParser * addParse = &addParsing;
			dataPackage = addParse->parseAndReturn(arguments);
			deployer.executeAdd(dataPackage);
		}
		else if (command == "edit"){
			EditParser editParsing;
			BaseClassParser * editParse = &editParsing;
			dataPackage = editParse->parseAndReturn(arguments);
			deployer.executeEdit(dataPackage, displayDate, searchKeywords, displayCase);
		}
		else if (command == "delete"){
			DeleteParser deleteParsing;
			BaseClassParser * deleteParse = &deleteParsing;
			dataPackage = deleteParse->parseAndReturn(arguments);
			deployer.executeDelete(dataPackage, displayDate, searchKeywords, displayCase);
		}
		else if (command == "search"){
			SearchParser searchParsing;
			BaseClassParser * searchParse = &searchParsing;
			string argument = searchParse->parseSearchArgs(arguments);
			searchKeywords = deployer.executeSearch(argument);
			if (!searchKeywords.empty()) {
				displayCase = 1;
			}
		}
		else if (command == "undo"){
			deployer.executeUndo();
		}
		else if (command == "redo"){
			deployer.executeRedo();
		}
		else if (command == "complete"){
			CompleteParser completeParsing;
			BaseClassParser * completeParse = &completeParsing;
			dataPackage = completeParse->parseAndReturn(arguments);
			deployer.executeComplete(dataPackage, displayDate, searchKeywords, displayCase);
		}
		else if (command == "uncomplete"){
			CompleteParser completeParsing;
			BaseClassParser * completeParse = &completeParsing;
			dataPackage = completeParse->parseAndReturn(arguments);
			deployer.executeUncomplete(dataPackage, displayDate, searchKeywords, displayCase);
		}
		else if (command == "slot") {
			//This will be handled by updateLineText(). This will ensure exception does not occur.
		}
		else {
			throw runtime_error("No Actionable Commands for Input Found");
		}
	}
	catch (const exception& ex){

	}
}

vector<string> ProgramController::populateSuggestionBox(string input)
{
	CommandAndArgumentParser inputParse(input);

	command = inputParse.command;
	arguments = inputParse.arguments;

	vector<string> suggestions;

	if (command == "search") {
		SearchParser searchParsing;
		BaseClassParser * searchParse = &searchParsing;
		string argument = searchParse->parseSearchArgs(arguments);
		suggestions = deployer.executeSearch(argument);
	}
	return suggestions;
}

void ProgramController::executeSuggestionSelection(string selection, string lineText)
{
	CommandAndArgumentParser inputParse(lineText);
	string command = inputParse.command;

	if (command == "search") {
		searchKeywords.clear();
		searchKeywords.push_back(selection);
		displayCase = 1;
	}
	refreshTableDisplay();
}

vector<vector<string>> ProgramController::refreshTableDisplay()
{
	return displayTable(displayDate);
}

vector<vector<string>> ProgramController::displayTable(string date)
{
	vector<vector<string>> forTableDisplay;
	try {
		DisplayLogic displayer(fileName, displayDate, searchKeywords, displayCase);
		forTableDisplay = displayer.displayEvents();
		return forTableDisplay;
	}
	catch (const exception& ex){
		return forTableDisplay;
	}
}

string ProgramController::updateLineText(string inputText, bool isEnterPressed)
{ 
	string completer;
	try{
		if (inputText == "add") {
			completer = "add [][][][]";
		}
		if (inputText == "slot") {
			completer = "slot [][][]";
		}
		else {
			CommandAndArgumentParser inputParse(inputText);
			string command = inputParse.command;
			string argument = inputParse.arguments;
			if (command == "edit" && inputText.substr(inputText.length() - 1, 1) == " " && !isEnterPressed) {
				EditParser editor;
				int argPosition = editor.convertToPosition(argument);
				if (argPosition >= 0)
				{
					DisplayLogic displayer(fileName, displayDate, searchKeywords, displayCase);
					string append = displayer.formatContentsToLineEdit(argPosition);
					completer = inputText + append;
				}
			}
			else if (command == "slot" && isEnterPressed) {
				SearchParser search;
				dataPackage = search.parsefreeSlotCheck(argument);
				SearchLogic searcher(fileName);
				pair <string, string> result = searcher.getEarliestFreeSlot(dataPackage.getLineEntries(), dataPackage.getStartEndPositions());
				if (!result.first.empty() && !result.second.empty()) {
					completer = "add [][" + result.first + "][" + result.second + "][]";
				}
			}
		}
		return completer;
	}
	catch (const exception& ex){
		return completer;
	}
}

pair<int, int> ProgramController::getCompletedStatToday()
{
	pair<int, int> stats;
	try {
		SearchLogic searcher(fileName);
		return searcher.getTodayCompletionStat(displayDate);
	}
	catch (const exception& ex){
		return stats;
	}
}



