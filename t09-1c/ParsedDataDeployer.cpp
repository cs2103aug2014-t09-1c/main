#include "stdafx.h"
#include "ParsedDataDeployer.h"


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
	if (newAdd.isEntryValid())
	{
		newAdd.commitAdd();
	}
	else
	{
		error = newAdd.getErrorString();
	}
}

void ParsedDataDeployer::executeDelete(ParsedDataPackage deletePackage, string fileName, int displayCase)
{
	DeleteLogic deleter(fileName, displayCase);
	deleter.deleteEntry(deletePackage.date, deletePackage.lineNum);
}

void ParsedDataDeployer::executeEdit(vector<ParsedDataPackage> editPackages, string fileName, int displayCase)
{
	ParsedDataPackage deletePackage = editPackages[0];
	ParsedDataPackage addPackage = editPackages[1];

	EditLogic newEdit(fileName, deletePackage.date, deletePackage.lineNum, displayCase);
	newEdit.appendEntry("name", addPackage.name);
	newEdit.appendEntry("date", addPackage.date);
	newEdit.appendEntry("start", addPackage.start);
	newEdit.appendEntry("end", addPackage.end);
	newEdit.appendEntry("category", addPackage.category);

	newEdit.editEntry();
}

void ParsedDataDeployer::executeSearch(ParsedDataPackage searchPackage, string fileName)//search for either name, date or category
{
	SearchLogic newSearch(fileName);
	if (searchPackage.name != ""){
		newSearch.searchEntry(name, searchPackage.name);//havent put search logic class
	}
	if (searchPackage.date != ""){
		newSearch.searchEntry(date, searchPackage.date);
	}
	if (searchPackage.category != ""){
		newSearch.searchEntry(category, searchPackage.category);
	}

}
void ParsedDataDeployer::executeUndo(string fileName)
{
	UndoLogic newUndo(fileName);
	newUndo.removeLastChange();
}

string ParsedDataDeployer::returnErrorString()
{
	return error;
}