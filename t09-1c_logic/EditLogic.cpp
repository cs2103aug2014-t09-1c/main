#include "stdafx.h"
#include "EditLogic.h"
#include "DeleteLogic.h"
#include "AddLogic.h"
#include "FileEntryFormatter.h"



EditLogic::EditLogic(FileLogic fileHandler) : fileHandler(""), addFunction(fileHandler)
{
	this->fileHandler = fileHandler;
}


EditLogic::~EditLogic()
{
}

void EditLogic::appendEntry(string attribute, string entry)
{
	addFunction.appendToLineEntry(attribute, entry);
}

void EditLogic::editEntry(string date, int position)
{
	DeleteLogic deleter(fileHandler);
	deleter.deleteEntry(date, position);
	string deletedLine = deleter.deletedEntry;
	int deletedPosition = deleter.deletedPosition;

	string oldCreationDate = FileEntryFormatter::getAttributeEntry("CreationDate", deletedLine);
	string newLine = addFunction.getLineEntry();
	newLine = FileEntryFormatter::editAttributedEntryFromLineEntry("CreationDate", oldCreationDate, newLine);
	addFunction.setLineEntry(newLine);

	if (addFunction.isEntryValid() && deletedPosition > -1) {
		fileHandler.addToPositionNumber(deletedPosition, newLine);
	}
}