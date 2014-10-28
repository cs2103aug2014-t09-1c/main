#include "stdafx.h"
#include "ParsedDataDeployer.h"
#include "AddLogic.h"
#include "DeleteLogic.h"
#include "EditLogic.h"
#include "SearchLogic.h"
#include "UndoLogic.h"
#include "CompleteLogic.h"

string ParsedDataDeployer::error = "";

ParsedDataDeployer::ParsedDataDeployer()
{
}


ParsedDataDeployer::~ParsedDataDeployer()
{
}

void ParsedDataDeployer::executeAdd(ParsedDataPackage addPackage, string fileName)
{
	AddLogic newAdd(fileName);
	newAdd.appendToLineEntry("name", addPackage.name);
	newAdd.appendToLineEntry("date", addPackage.date);	
	newAdd.appendToLineEntry("start", addPackage.start);
	newAdd.appendToLineEntry("end", addPackage.end);
	newAdd.appendToLineEntry("category", addPackage.category);
	newAdd.commitAdd();
	if (newAdd.errorPresent) {
		UndoLogic::instance()->storeUndo(fileName);
	}
	else {
		error = newAdd.getErrorString();
	}
}

void ParsedDataDeployer::executeDelete(ParsedDataPackage deletePackage, vector<string> keywords, string fileName, int displayCase)
{
	DeleteLogic deleter(fileName, displayCase);
	deleter.deleteEntry(deletePackage.date, keywords, deletePackage.lineNum);
	if (!deleter.deletedPosition.empty()) {
		UndoLogic::instance()->storeUndo(fileName, "delete", deleter.deletedEntry, deleter.deletedPosition);
	}
}

void ParsedDataDeployer::executeEdit(vector<ParsedDataPackage> editPackages, vector<string> keywords, string fileName, int displayCase)
{
	ParsedDataPackage deletePackage = editPackages[0];
	ParsedDataPackage addPackage = editPackages[1];

	EditLogic newEdit(fileName, deletePackage.date, keywords, deletePackage.lineNum, displayCase);
	newEdit.appendEntry("name", addPackage.name);
	newEdit.appendEntry("date", addPackage.date);
	newEdit.appendEntry("start", addPackage.start);
	newEdit.appendEntry("end", addPackage.end);
	newEdit.appendEntry("category", addPackage.category);

	newEdit.editEntry();

	if (newEdit.successfulEdit) {
		UndoLogic::instance()->storeUndo(fileName, newEdit.oldLine, newEdit.oldPosition);
	}
}

vector<string> ParsedDataDeployer::executeSearch(string searchPackage, string fileName)//search for either name, date or category
{
	SearchLogic newSearch(fileName);
	return newSearch.createKeywords(searchPackage);
	

}
void ParsedDataDeployer::executeUndo(string fileName)
{
	if (!UndoLogic::instance()->isUndoEmpty()) {
		UndoLogic::instance()->undo(fileName);
	}
}

void ParsedDataDeployer::executeRedo(string fileName)
{
	if (!UndoLogic::instance()->isRedoEmpty()) {
		UndoLogic::instance()->redo(fileName);
	}
}

void ParsedDataDeployer::executeComplete(ParsedDataPackage completePackage, vector<string> keywords, string fileName, int displayCase)
{
	CompleteLogic newComplete(fileName, displayCase);
	newComplete.complete(completePackage.date, keywords, completePackage.lineNum, completePackage.lineNum);
	UndoLogic::instance()->storeUndo(fileName, "modify", newComplete.originalFileEntries, newComplete.fileEntryPositions);
}

string ParsedDataDeployer::returnErrorString()
{
	return error;
}