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
void EditLogic::appendOldCreationDate() 
{
	string oldDate = FileEntryFormatter::getAttributeEntry("CreationDate", oldLine);
	lineText = FileEntryFormatter::editAttributedEntryFromLineEntry("CreationDate", oldDate, lineText);
}

void EditLogic::editEntry()
{
	FileLogic fileHandler(fileName);
	if (verifyLine() && oldPosition > -1) {
		appendOldCreationDate();
		fileHandler.addToPositionNumber(oldPosition, lineText);
	}
	else {
		fileHandler.addToPositionNumber(oldPosition, oldLine);
	}
}