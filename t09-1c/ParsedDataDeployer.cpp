//@author A0116410Y
#include "stdafx.h"
#include "ParsedDataDeployer.h"
#include "AddLogic.h"
#include "DeleteLogic.h"
#include "EditLogic.h"
#include "SearchLogic.h"
#include "UndoLogic.h"
#include "CompleteLogic.h"
#include "DisplayLogic.h"

ParsedDataDeployer::ParsedDataDeployer(string fileName)
{
	this->fileName = fileName;
}

ParsedDataDeployer::ParsedDataDeployer(vector<string> testVector)
{
	isTestMode = true;
	testVectorStore = testVector;
}

ParsedDataDeployer::~ParsedDataDeployer()
{
}

void ParsedDataDeployer::executeAdd(ParsedDataPackage addPackage)
{
	try {
		if (!isTestMode) {
			AddLogic newAdd(fileName);
			BaseClassLogic * add = &newAdd;
			add->execute(addPackage.getLineEntries());
			UndoLogic::instance()->storeUndo(fileName);
		}
		else {
			AddLogic newAdd(testVectorStore);
			BaseClassLogic * add = &newAdd;
			add->execute(addPackage.getLineEntries());
			testVectorStore = add->getEntriesVector();
		}
		consoleString = COMPLETED_ADD;
	}
	catch (const exception& ex){
		consoleString = ex.what();
	}
}

void ParsedDataDeployer::executeDelete(ParsedDataPackage deletePackage, string date, vector<string> keywords, int displayCase)
{
	try {
		if (!isTestMode) {
			DeleteLogic newDelete(fileName, date, keywords, displayCase);
			BaseClassLogic * deleter = &newDelete;
			deleter->execute(deletePackage.getStartEndPositions());
			UndoLogic::instance()->storeUndo(fileName, "delete", deleter->getLinesForUndo(), deleter->getPosForUndo());
		}
		else {
			DeleteLogic newDelete(testVectorStore, date, keywords, displayCase);
			BaseClassLogic * deleter = &newDelete;
			deleter->execute(deletePackage.getStartEndPositions());
			testVectorStore = deleter->getEntriesVector();
		}
		consoleString = COMPLETED_DELETE;
	}
	catch (const exception& ex){
		consoleString = ex.what();
	}
}

void ParsedDataDeployer::executeEdit(ParsedDataPackage editPackage, string date , vector<string> keywords, int displayCase)
{
	try {
		if (!isTestMode) {
			EditLogic newEdit(fileName, date, keywords, displayCase);
			BaseClassLogic * edit = &newEdit;
			edit->execute(editPackage.getStartEndPositions(), editPackage.getLineEntries());
			UndoLogic::instance()->storeUndo(fileName, "modify", edit->getLinesForUndo(), edit->getPosForUndo());
		}
		else {
			EditLogic newEdit(testVectorStore, date, keywords, displayCase);
			BaseClassLogic * edit = &newEdit;
			edit->execute(editPackage.getStartEndPositions(), editPackage.getLineEntries());
			testVectorStore = edit->getEntriesVector();
		}
		consoleString = COMPLETED_EDIT;
	}
	catch (const exception& ex){
		consoleString = ex.what();
	}
}

vector<string> ParsedDataDeployer::executeSearch(string searchPackage)
{
	vector<string> keywords;
	try {
		if (!isTestMode) {
			SearchLogic newSearch(fileName);
			BaseClassLogic * search = &newSearch;
			keywords = search->createKeywords(searchPackage);
		}
		else {
			SearchLogic newSearch(testVectorStore);
			BaseClassLogic * search = &newSearch;
			keywords = search->createKeywords(searchPackage);
		}
		string size = std::to_string(keywords.size());
		consoleString = SEARCH_RESULTS(size);
		return keywords;
	}
	catch (const exception& ex){
		consoleString = ex.what();
		return keywords;
	}
}

void ParsedDataDeployer::executeUndo()
{
	if (!UndoLogic::instance()->isUndoEmpty()) {
		UndoLogic::instance()->undo(fileName);
		consoleString = COMPLETED_UNDO;
	}
	else {
		consoleString = FAILED_UNDO;
	}
}

void ParsedDataDeployer::executeRedo()
{
	if (!UndoLogic::instance()->isRedoEmpty()) {
		UndoLogic::instance()->redo(fileName);
		consoleString = COMPLETED_REDO;
	}
	else {
		consoleString = FAILED_REDO;
	}
}

void ParsedDataDeployer::executeComplete(ParsedDataPackage completePackage, string date, vector<string> keywords, int displayCase)
{
	try {
		if (!isTestMode) {
			CompleteLogic newComplete(fileName, date, keywords, displayCase);
			BaseClassLogic * completer = &newComplete;
			completer->execute(completePackage.getStartEndPositions(), COMPLETE);
			UndoLogic::instance()->storeUndo(fileName, "modify", completer->getLinesForUndo(), completer->getPosForUndo());
		}
		else {
			CompleteLogic newComplete(testVectorStore, date, keywords, displayCase);
			BaseClassLogic * completer = &newComplete;
			completer->execute(completePackage.getStartEndPositions(), COMPLETE);
			testVectorStore = completer->getEntriesVector();
		}
		consoleString = COMPLETED_COMPLETE;
	}
	catch (const exception& ex){
		consoleString = ex.what();
	}
}

void ParsedDataDeployer::executeUncomplete(ParsedDataPackage uncompletePackage, string date, vector<string> keywords, int displayCase)
{
	try {
		if (!isTestMode) {
			CompleteLogic newComplete(fileName, date, keywords, displayCase);
			BaseClassLogic * completer = &newComplete;
			completer->execute(uncompletePackage.getStartEndPositions(), UNCOMPLETE);
			UndoLogic::instance()->storeUndo(fileName, "modify", completer->getLinesForUndo(), completer->getPosForUndo());
		}
		else {
			CompleteLogic newComplete(testVectorStore, date, keywords, displayCase);
			BaseClassLogic * completer = &newComplete;
			completer->execute(uncompletePackage.getStartEndPositions(), UNCOMPLETE);
			testVectorStore = completer->getEntriesVector();
		}
		consoleString = COMPLETED_UNCOMPLETE;
	}
	catch (const exception& ex){
		consoleString = ex.what();
	}
}

vector<vector<string>> ParsedDataDeployer::getDisplayEvents(string date, vector<string> keywords, int displayCase)
{
	vector<vector<string>> displayEventList;
	try {
		if (!isTestMode) {
			DisplayLogic newDisplay(fileName, date, keywords, displayCase);
			BaseClassLogic * displayer = &newDisplay;
			displayEventList = displayer->displayEvents();
		}
		else {
			DisplayLogic newDisplay(testVectorStore, date, keywords, displayCase);
			BaseClassLogic * displayer = &newDisplay;
			displayEventList = displayer->displayEvents();
		}
		return displayEventList;
	}
	catch (const exception& ex){
		consoleString = ex.what();
		return displayEventList;
	}
}

string ParsedDataDeployer::executeFormatContentsToLineEdit(int position, string date, vector<string> keywords, int displayCase)
{
	string contentFormatter;
	try {
		if (!isTestMode) {
			DisplayLogic newDisplay(fileName, date, keywords, displayCase);
			BaseClassLogic * displayer = &newDisplay;
			contentFormatter = displayer->formatContentsToLineEdit(position);
		}
		else {
			DisplayLogic newDisplay(testVectorStore, date, keywords, displayCase);
			BaseClassLogic * displayer = &newDisplay;
			contentFormatter = displayer->formatContentsToLineEdit(position);
		}
		return contentFormatter;
	}
	catch (const exception& ex){
		consoleString = ex.what();
		return contentFormatter;
	}
}

pair <string, string> ParsedDataDeployer::executeGetEarliestFreeSlot(ParsedDataPackage freeSlotPackage)
{
	pair <string, string> freeSlotData;
	try {
		if (!isTestMode) {
			SearchLogic newSearch(fileName);
			BaseClassLogic * search = &newSearch;
			freeSlotData = search->getEarliestFreeSlot(freeSlotPackage.getLineEntries(), freeSlotPackage.getStartEndPositions());
		}
		else {
			SearchLogic newSearch(testVectorStore);
			BaseClassLogic * search = &newSearch;
			freeSlotData = search->getEarliestFreeSlot(freeSlotPackage.getLineEntries(), freeSlotPackage.getStartEndPositions());
		}
		return freeSlotData;
	}
	catch (const exception& ex){
		consoleString = ex.what();
		return freeSlotData;
	}
}

pair<int, int> ParsedDataDeployer::executeGetTodayCompletionStat(string todayDate)
{
	pair<int, int> completionStat;
	try {
		if (!isTestMode) {
			SearchLogic newSearch(fileName);
			BaseClassLogic * search = &newSearch;
			completionStat = search->getTodayCompletionStat(todayDate);
		}
		else {
			SearchLogic newSearch(testVectorStore);
			BaseClassLogic * search = &newSearch;
			completionStat = search->getTodayCompletionStat(todayDate);
		}
		return completionStat;
	}
	catch (const exception& ex){
		consoleString = ex.what();
		return completionStat;
	}
}

string ParsedDataDeployer::returnConsoleString()
{
	return consoleString;
}

void ParsedDataDeployer::clearConsoleString()
{
	consoleString.clear();
}

vector<string> ParsedDataDeployer::returnTestVector()
{
	return testVectorStore;
}