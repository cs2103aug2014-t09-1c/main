//@author A0116410Y
#include "stdafx.h"
#include "ProgramController.h"
#include "ParsedDataDeployer.h"
#include "ParsedDataPackage.h"
#include <vector>
#include "CompleteParser.h"

//after an input is scanned by UI method, call to method sendToParse is made to send input to Parser
//after Parser returns the variables in ParsedDataPackage, send the details to logic
//after file output returns an output, controller sends it to UI

ProgramController::ProgramController(string fileName) : deployer(fileName)
{
	this->fileName = fileName;
	file.open(fileName, ios::out | ios::app);
	file << "";
	displayDate = getTodayDateInString();
	consoleString = WELCOME_MESSAGE;
}

ProgramController::ProgramController(vector<string> testVector) : deployer(testVector)
{
	isTestMode = true;
	displayDate = getTodayDateInString();
}

ProgramController::~ProgramController()
{
	if (!isTestMode) {
		file.close();
	}
}

void ProgramController::executeEntry(string input)
{
	clearConsoleString();
	CommandAndArgumentParser inputParse(input);

	command = inputParse.getCommand();
	arguments = inputParse.getArguments();

	if (command == HOME_COMMAND) {
		executeHomeCommand();
	}
	else if (command == ALL_COMMAND) {
		executeAllCommand();
	}
	else if (command == ADD_COMMAND) {
		executeAddCommand();
	}
	else if (command == EDIT_COMMAND){
		executeEditCommand();
	}
	else if (command == DELETE_COMMAND){
		executeDeleteCommand();
	}
	else if (command == SEARCH_COMMAND){
		executeSearchCommand();
	}
	else if (command == UNDO_COMMAND){
		executeUndoCommand();
	}
	else if (command == REDO_COMMAND){
		executeRedoCommand();
	}
	else if (command == COMPLETE_COMMAND){
		executeCompleteCommand();
	}
	else if (command == UNCOMPLETE_COMMAND){
		executeUncompleteCommand();
	}
	else if (command == SLOT_COMMAND) {
		//This will be handled by updateLineText(). This will ensure exception does not occur.
	}
	else if (command == CLIP_COMMAND) {
		updateLineText(input, true);
	}
	else {
		executeAddNaturalParsing(input);
	}
}

void ProgramController::executeHomeCommand()
{
	displayCase = DISPLAY_HOME_CASE;
	searchKeywords.clear();
	consoleString = DISPLAY_CHANGE;
}

void ProgramController::executeAllCommand()
{
	displayCase = DISPLAY_ALL_CASE;
	searchKeywords.clear();
	consoleString = DISPLAY_CHANGE;
}

void ProgramController::executeAddCommand()
{
	try {
		AddParser addParsing;
		BaseClassParser * addParse = &addParsing;
		dataPackage = addParse->parseAndReturn(arguments);
		deployer.executeAdd(dataPackage);
		consoleString = deployer.returnConsoleString();
	}
	catch (const exception& ex){
		consoleString = ex.what();
	}
}
void ProgramController::executeEditCommand()
{
	try {
		EditParser editParsing;
		BaseClassParser * editParse = &editParsing;
		dataPackage = editParse->parseAndReturn(arguments);
		deployer.executeEdit(dataPackage, displayDate, searchKeywords, displayCase);
		consoleString = deployer.returnConsoleString();
	}
	catch (const exception& ex){
		consoleString = ex.what();
	}
}

void ProgramController::executeDeleteCommand()
{
	try {
		DeleteParser deleteParsing;
		BaseClassParser * deleteParse = &deleteParsing;
		dataPackage = deleteParse->parseAndReturn(arguments);
		deployer.executeDelete(dataPackage, displayDate, searchKeywords, displayCase);
		consoleString = deployer.returnConsoleString();
	}
	catch (const exception& ex){
		consoleString = ex.what();
	}
}

void ProgramController::executeSearchCommand()
{
	try {
		SearchParser searchParsing;
		BaseClassParser * searchParse = &searchParsing;
		string argument = searchParse->parseSearchArgs(arguments);
		searchKeywords = deployer.executeSearch(argument);
		consoleString = deployer.returnConsoleString();
		if (!searchKeywords.empty()) {
			displayCase = DISPLAY_KEYWORD_CASE;
		}
	}
	catch (const exception& ex){
		consoleString = ex.what();
	}
}

void ProgramController::executeUndoCommand()
{
	deployer.executeUndo();
	consoleString = deployer.returnConsoleString();
}

void ProgramController::executeRedoCommand()
{
	deployer.executeRedo();
	consoleString = deployer.returnConsoleString();
}

void ProgramController::executeCompleteCommand()
{
	try {
		CompleteParser completeParsing;
		BaseClassParser * completeParse = &completeParsing;
		dataPackage = completeParse->parseAndReturn(arguments);
		deployer.executeComplete(dataPackage, displayDate, searchKeywords, displayCase);
		consoleString = deployer.returnConsoleString();
	}
	catch (const exception& ex){
		consoleString = ex.what();
	}
}

void ProgramController::executeUncompleteCommand()
{
	try {
		CompleteParser completeParsing;
		BaseClassParser * completeParse = &completeParsing;
		dataPackage = completeParse->parseAndReturn(arguments);
		deployer.executeUncomplete(dataPackage, displayDate, searchKeywords, displayCase);
		consoleString = deployer.returnConsoleString();
	}
	catch (const exception& ex){
		consoleString = ex.what();
	}
}

void ProgramController::executeAddNaturalParsing(string input)
{
	try {
		AddParser addParsing;
		BaseClassParser * addParse = &addParsing;
		dataPackage = addParse->parseNLAndReturn(input);
		deployer.executeAdd(dataPackage);
		consoleString = deployer.returnConsoleString();
	}
	catch (const exception& ex){
		consoleString = ex.what();
	}
}

vector<string> ProgramController::populateSuggestionBox(string input)
{
	CommandAndArgumentParser inputParse(input);

	command = inputParse.getCommand();
	arguments = inputParse.getArguments();

	vector<string> suggestions;

	if (command == SEARCH_COMMAND) {
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
	string command = inputParse.getCommand();

	if (command == SEARCH_COMMAND) {
		searchKeywords.clear();
		searchKeywords.push_back(selection);
		displayCase = DISPLAY_KEYWORD_CASE;
		consoleString = SELECT_KEYWORD;
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
	forTableDisplay = deployer.getDisplayEvents(date, searchKeywords, displayCase);
	return forTableDisplay;
}

string ProgramController::updateLineText(string inputText, bool isEnterPressed)
{ 
	string completer;
	CommandAndArgumentParser inputParse(inputText);
	command = inputParse.getCommand();
	arguments = inputParse.getArguments();
	if (command == ADD_COMMAND && arguments.empty()) {
		completer = executeAddFormatLineUpdater();
	}
	else if (command == SLOT_COMMAND && arguments.empty()) {
		completer = executeSlotFormatLineUpdater();
	}
	else if (command == EDIT_COMMAND && inputText.substr(inputText.length() - 1, 1) == " " && !isEnterPressed) {
		completer = executeEditLineUpdater(inputText);
	}
	else if (command == CLIP_COMMAND && ((inputText.substr(inputText.length() - 1, 1) == " "  && !isEnterPressed) || isEnterPressed)) {
		completer = executeClipLineUpdater(arguments);
	}
	else if (command == SLOT_COMMAND && isEnterPressed) {
		completer = executeSlotLineUpdater(arguments);
	}
	return completer;
}

string ProgramController::executeAddFormatLineUpdater()
{
	string empty;
	return ADD_FORMAT(empty, empty, empty, empty);
}

string ProgramController::executeSlotFormatLineUpdater()
{
	return SLOT_FORMAT;
}

string ProgramController::executeEditLineUpdater(string inputText)
{
	string completer;
	try {
		EditParser newEdit;
		BaseClassParser * edit = &newEdit;
		int argPosition = edit->convertToPosition(arguments);
		if (argPosition >= 0) {
			string append = deployer.executeFormatContentsToLineEdit(argPosition, displayDate, searchKeywords, displayCase);
			completer = inputText + append;
		}
		return completer;
	}
	catch (const exception& ex){
		consoleString = ex.what();
		return completer;
	}
}

string ProgramController::executeClipLineUpdater(string arguments)
{
	string completer;
	try {
		EditParser newEdit;
		BaseClassParser * edit = &newEdit;
		int argPosition = edit->convertToPosition(arguments);
		if (argPosition >= 0)
		{
			string append = deployer.executeFormatContentsToLineEdit(argPosition, displayDate, searchKeywords, displayCase);
			if (!append.empty()) {
				completer = ADD_APPEND + append;
				consoleString = SUCCESS_CLIP(arguments);
			}
			else {
				consoleString = CLIP_ERROR;
			}
		}
		else {
			consoleString = CLIP_ERROR;
		}
		return completer;
	}
	catch (const exception& ex){
		consoleString = ex.what();
		return completer;
	}
}

string ProgramController::executeSlotLineUpdater(string arguments)
{
	string completer;
	try {
		SearchParser newSearch;
		BaseClassParser * search = &newSearch;
		dataPackage = search->parsefreeSlotCheck(arguments);
		pair <string, string> result = deployer.executeGetEarliestFreeSlot(dataPackage);
		if (!result.first.empty() && !result.second.empty()) {
			string empty;
			completer = ADD_FORMAT(empty, result.first, result.second, empty);
			consoleString = SLOTS_AVAILABLE(result.first, result.second);
		}
		else {
			consoleString = NO_SLOTS_AVAILABLE;
		}
		return completer;
	}
	catch (const exception& ex){
		consoleString = ex.what();
		return completer;
	}
}

pair<int, int> ProgramController::getCompletedStatToday()
{
	return deployer.executeGetTodayCompletionStat(displayDate);
}

vector<string> ProgramController::returnTestVector()
{
	return deployer.returnTestVector();
}

string ProgramController::getConsoleString()
{
	return consoleString;
}

void ProgramController::clearConsoleString()
{
	consoleString.clear();
	deployer.clearConsoleString();
}

string ProgramController::getTodayDateInString()
{
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);

	char buffer[80];
	strftime(buffer, 80, "%d/%m/%Y", now);
	string out = buffer;

	return out;
}