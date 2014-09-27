#include "stdafx.h"
#include "AddLogic.h"
#include "FileEntryFormatter.h"
#include <string>
#include <iostream>


AddLogic::AddLogic(string fileName) : fileHandler(fileName)
{
	string creationDate = FileEntryFormatter::createAttributedEntry("CreationDate", TimeLogic::getTimeNowInString());
	lineEntry = FileEntryFormatter::addAttributedEntryToLineEntry(creationDate, lineEntry);
}


AddLogic::~AddLogic()
{
}

void AddLogic::appendToLineEntry(string attribute, string entry)
{
	string attributedEntry = FileEntryFormatter::createAttributedEntry(attribute, entry);
	lineEntry = FileEntryFormatter::addAttributedEntryToLineEntry(attributedEntry, lineEntry);
}


void AddLogic::commitAdd()
{
	fileHandler.appendToFile(lineEntry);
}