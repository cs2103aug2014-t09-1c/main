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
	if (FileEntryFormatter::getAttributeEntry("start", lineEntry) == "") {
		if (FileEntryFormatter::getAttributeEntry("end", lineEntry) == "") {
			if (FileEntryFormatter::getAttributeEntry("date", lineEntry) == "") {	
				if (FileEntryFormatter::getAttributeEntry("name", lineEntry) == "") {
					//empty
				}
				else {
					appendToLineEntry("type", "float");
				}
			}
			else {
				lineEntry = FileEntryFormatter::editAttributedEntryFromLineEntry("end", "23:59", lineEntry);
				appendToLineEntry("type", "deadline");
			}
		}
		else {
			appendToLineEntry("type", "deadline");
		}
	}
	else {
		appendToLineEntry("type", "timed");
	}

	fileHandler.appendToFile(lineEntry);
}