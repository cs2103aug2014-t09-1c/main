#include "stdafx.h"
#include "EditLogic.h"
#include "FileEntryFormatter.h"



EditLogic::EditLogic(string fileName, string date, int position)
{
	this->fileName = fileName;
	initiateLineText();
	deleteLine(date, position);
}


EditLogic::~EditLogic()
{
}

void EditLogic::initiateLineText() 
{
	string creationDate = FileEntryFormatter::createAttributedEntry("CreationDate", TimeLogic::getTimeNowInString());
	lineText = FileEntryFormatter::addAttributedEntryToLineEntry(creationDate, lineText);
}

void EditLogic::deleteLine(string date, int position)
{
	DeleteLogic deleter(fileName);
	deleter.deleteEntry(date, position);
	oldLine = deleter.deletedEntry;
	oldPosition = deleter.deletedPosition;
}

void EditLogic::appendEntry(string attribute, string entry)
{
	string newEntry = FileEntryFormatter::createAttributedEntry(attribute, entry);
	lineText = FileEntryFormatter::addAttributedEntryToLineEntry(newEntry, lineText);
}

bool EditLogic::verifyLine()
{
	AddLogic addFunction(fileName);
	addFunction.setLineEntry(lineText);
	if (addFunction.isEntryValid()) {
		lineText = addFunction.getLineEntry();
		return true;
	}
	else {
		return false;
	}
}

void EditLogic::editEntry()
{
	if (verifyLine() && oldPosition > -1) {
		FileLogic fileHandler(fileName);
		fileHandler.addToPositionNumber(oldPosition, lineText);
	}
}