#include "stdafx.h"
#include "ParsedDataDeployer.h"


ParsedDataDeployer::ParsedDataDeployer()
{
}


ParsedDataDeployer::~ParsedDataDeployer()
{
}

void ParsedDataDeployer::executeAdd(ParsedDataPackage addPackage, FileLogic fileHandler)
{
	AddLogic newAdd(fileHandler);
	newAdd.appendToLineEntry("name", addPackage.name);
	newAdd.appendToLineEntry("date", addPackage.date);
	newAdd.appendToLineEntry("category", addPackage.category);
	newAdd.appendToLineEntry("start", addPackage.start);
	newAdd.appendToLineEntry("end", addPackage.end);
	newAdd.commitAdd();
}

void ParsedDataDeployer::executeDelete(ParsedDataPackage deletePackage, FileLogic fileHandler)
{
	DeleteLogic deleter(fileHandler);
	deleter.deleteEntry(deletePackage.date, deletePackage.lineNum);
}

void ParsedDataDeployer::executeEdit(vector<ParsedDataPackage> editPackages, FileLogic fileHandler)
{
	ParsedDataPackage deletePackage = editPackages[0];
	ParsedDataPackage addPackage = editPackages[1];

	EditLogic newEdit(fileHandler);
	newEdit.appendEntry("name", addPackage.name);
	newEdit.appendEntry("date", addPackage.date);
	newEdit.appendEntry("category", addPackage.category);
	newEdit.appendEntry("start", addPackage.start);
	newEdit.appendEntry("end", addPackage.end);

	newEdit.editEntry(deletePackage.date, deletePackage.lineNum);
}