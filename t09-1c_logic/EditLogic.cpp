#include "stdafx.h"
#include "EditLogic.h"
#include "FileEntryFormatter.h"



EditLogic::EditLogic(string fileName, string date, vector<string> keywords, int position, int displayCase)
{
	this->displayCase = displayCase;
	this->fileName = fileName;
	initiateLineText();
	deleteLine(date, keywords, position);

}


EditLogic::~EditLogic()
{
}

void EditLogic::initiateLineText() 
{
	string creationDate = FileEntryFormatter::createAttributedEntry("CreationDate", TimeLogic::getTimeNowInString());
	lineText = FileEntryFormatter::addAttributedEntryToLineEntry(creationDate, lineText);
}

void EditLogic::deleteLine(string date, vector<string> keywords, int position)
{
	DeleteLogic deleter(fileName, displayCase);
	deleter.deleteEntry(date, keywords, position);
	oldLine = deleter.deletedEntry.top();
	oldPosition = deleter.deletedPosition.top();
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
		successfulEdit = true;
	}
	else {
		fileHandler.addToPositionNumber(oldPosition, oldLine);
	}
}