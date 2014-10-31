#include "stdafx.h"
#include "ProgramController.h"
#include "ParsedDataDeployer.h"
#include "ParsedDataPackage.h"
#include <vector>
#include "DisplayLogic.h"
#include "TimeParser.h"
#include "CompleteParser.h"

//after an input is scanned by UI method, call to method sendToParse is made to send input to Parser
//after Parser returns the variables in ParsedDataPackage, send the details to logic
//after file output returns an output, controller sends it to UI

ProgramController::ProgramController(string fileName)
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

	if (command == "home") {
		displayCase = 0;
		searchKeywords.clear();
	}

	else if (command == "add") {
		AddParser addParsing;
		dataPackage = addParsing.parseAndReturn(arguments);
		if (addParsing.isInputValid())
		{
			errorString = addParsing.getErrorString();
		}
		else
		{
			ParsedDataDeployer::executeAdd(dataPackage, fileName);
		}
		
	}
	else if (command == "edit"){
		EditParser editParsing;
		dataPackages = editParsing.parseAndReturn(arguments);
		if (dataPackages[0].date.empty()) {
			ParsedDataPackage deletePack = dataPackages[0];
			deletePack.date = displayDate;
			dataPackages[0] = deletePack;
			ParsedDataDeployer::executeEdit(dataPackages, searchKeywords, fileName, displayCase);
		}
		else {
			ParsedDataDeployer::executeEdit(dataPackages, searchKeywords, fileName, displayCase);
		}
	}
	else if (command == "delete"){
		DeleteParser deleteParsing;
		dataPackage = deleteParsing.parseAndReturn(arguments);
		if (deleteParsing.isInputValid())
		{
			errorString = deleteParsing.getErrorString();
		}
		else if (dataPackage.date.empty())
		{
			dataPackage.date = displayDate;
			for (int i = 0; i < deleteParsing.getRepetition(); i++){
				ParsedDataDeployer::executeDelete(dataPackage, searchKeywords, fileName, displayCase);
			}
		}
		else {
			for (int i = 0; i < deleteParsing.getRepetition(); i++){
				ParsedDataDeployer::executeDelete(dataPackage, searchKeywords, fileName, displayCase);
			}
		}
	}
	else if (command == "search"){
		SearchParser searchParsing;
		string argument = searchParsing.parseAndReturn(arguments);
		if (searchParsing.isInputValid())
		{
			errorString = searchParsing.getErrorString();
		}
		else {
			searchKeywords = ParsedDataDeployer::executeSearch(argument, fileName);
			if (searchKeywords.size() > 0) {
				displayCase = 1;
			}
		}
	}
	else if (command == "undo"){
		ParsedDataDeployer::executeUndo(fileName);
	}
	else if (command == "redo"){
		ParsedDataDeployer::executeRedo(fileName);
	}
	else if (command == "complete"){
		CompleteParser completeParsing;
		dataPackage = completeParsing.parseAndReturn(arguments);
		if (completeParsing.isInputValid())
		{
			//errorString = completeParsing.getErrorString();
		}
		else if (dataPackage.date.empty()) {
			dataPackage.date = displayDate;
			for (int i = 0; i < completeParsing.getRepetition(); i++){
				ParsedDataDeployer::executeComplete(dataPackage, searchKeywords, fileName, displayCase);
				dataPackage.lineNum++;
			}
		}
		else {
			for (int i = 0; i < completeParsing.getRepetition(); i++){
				ParsedDataDeployer::executeComplete(dataPackage, searchKeywords, fileName, displayCase);
				dataPackage.lineNum++;
			}
		}

	}
	else if (command == "uncomplete"){
		CompleteParser completeParsing;
		dataPackage = completeParsing.parseAndReturn(arguments);
		if (completeParsing.isInputValid())
		{
			//errorString = completeParsing.getErrorString();
		}
		else if (dataPackage.date.empty()) {
			dataPackage.date = displayDate;
			ParsedDataDeployer::executeUncomplete(dataPackage, searchKeywords, fileName, displayCase);
		}
		else {
			ParsedDataDeployer::executeUncomplete(dataPackage, searchKeywords, fileName, displayCase);
		}
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
		string argument = searchParsing.parseAndReturn(arguments);
		suggestions = ParsedDataDeployer::executeSearch(argument, fileName);
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
	DisplayLogic displayer(fileName);
	if (displayCase == 0) {
		forTableDisplay = displayer.collectEventsFromDate(date);
	}
	else {
		forTableDisplay = displayer.collectEventsWithKeywords(searchKeywords, date);
	}
	return forTableDisplay;
}

string ProgramController::updateLineText(string inputText)
{
	string completer;
	if (inputText == "add") {
		completer = "add [][][][]";
	}
	else {
		CommandAndArgumentParser inputParse(inputText);
		string command = inputParse.command;
		string argument = inputParse.arguments;
		if (command == "edit" && inputText.substr(inputText.length() - 1, 1) == " ") {
			int argPosition = EditParser::convertToPosition(argument);
			if (argPosition >= 0)
			{
				DisplayLogic displayer(fileName);
				string append = displayer.formatContentsToLineEdit(argPosition, searchKeywords, displayDate, displayCase);
				completer = inputText + append;
			}
		}
	}
	return completer;
}

void ProgramController::ConnectToDoListOutput(vector<string> vectorOutput)//input from other logic class a string lineEntry with attributes tags
{
	//send to UI e.g. >>> vectorOutput.parseFileToMemoryVector(FILENAME);


}



