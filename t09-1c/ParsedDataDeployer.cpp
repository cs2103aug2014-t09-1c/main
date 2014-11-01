#include "stdafx.h"
#include "ParsedDataDeployer.h"
#include "AddLogic.h"
#include "DeleteLogic.h"
#include "EditLogic.h"
#include "SearchLogic.h"
#include "UndoLogic.h"
#include "CompleteLogic.h"

string ParsedDataDeployer::error = "";

ParsedDataDeployer::ParsedDataDeployer(string fileName)
{
	this->fileName = fileName;
}


ParsedDataDeployer::~ParsedDataDeployer()
{
}

void ParsedDataDeployer::executeAdd(ParsedDataPackage addPackage)
{
	try {
		AddLogic newAdd(fileName);
		BaseClassLogic * add = &newAdd;
		add->execute(addPackage.getLineEntries());
		UndoLogic::instance()->storeUndo(fileName);
	}
	catch (const exception& ex){
	
	}
}

void ParsedDataDeployer::executeDelete(ParsedDataPackage deletePackage, string date, vector<string> keywords, int displayCase)
{
	try {
		DeleteLogic newDelete(fileName, date, keywords, displayCase);
		BaseClassLogic * deleter = &newDelete;
		deleter->execute(deletePackage.getStartEndPositions());
		UndoLogic::instance()->storeUndo(fileName, "delete", deleter->getLinesForUndo(), deleter->getPosForUndo());
	}
	catch (const exception& ex){

	}
}

void ParsedDataDeployer::executeEdit(ParsedDataPackage editPackage, string date , vector<string> keywords, int displayCase)
{
	try {
	EditLogic newEdit(fileName, date, keywords, displayCase);
	BaseClassLogic * edit = &newEdit;
	edit->execute(editPackage.getStartEndPositions(), editPackage.getLineEntries());
	UndoLogic::instance()->storeUndo(fileName, "modify", edit->getLinesForUndo(), edit->getPosForUndo());
	}
	catch (const exception& ex){

	}
}

vector<string> ParsedDataDeployer::executeSearch(string searchPackage)//search for either name, date or category
{
	SearchLogic newSearch(fileName);
	return newSearch.createKeywords(searchPackage);
}

void ParsedDataDeployer::executeUndo()
{
	if (!UndoLogic::instance()->isUndoEmpty()) {
		UndoLogic::instance()->undo(fileName);
	}
}

void ParsedDataDeployer::executeRedo()
{
	if (!UndoLogic::instance()->isRedoEmpty()) {
		UndoLogic::instance()->redo(fileName);
	}
}

void ParsedDataDeployer::executeComplete(ParsedDataPackage completePackage, string date, vector<string> keywords, int displayCase)
{
	try {
		CompleteLogic newComplete(fileName, date, keywords, displayCase);
		BaseClassLogic * completer = &newComplete;
		completer->execute(completePackage.getStartEndPositions(), 1);
		UndoLogic::instance()->storeUndo(fileName, "modify", completer->getLinesForUndo(), completer->getPosForUndo());
	}
	catch (const exception& ex){

	}
}

void ParsedDataDeployer::executeUncomplete(ParsedDataPackage uncompletePackage, string date, vector<string> keywords, int displayCase)
{
	try {
		CompleteLogic newComplete(fileName, date, keywords, displayCase);
		BaseClassLogic * completer = &newComplete;
		completer->execute(uncompletePackage.getStartEndPositions(), 0);
		UndoLogic::instance()->storeUndo(fileName, "modify", completer->getLinesForUndo(), completer->getPosForUndo());
	}
	catch (const exception& ex){

	}
}

string ParsedDataDeployer::returnErrorString()
{
	return error;
}