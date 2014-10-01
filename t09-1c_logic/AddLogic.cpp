#include "stdafx.h"
#include "AddLogic.h"
#include "FileEntryFormatter.h"
#include <string>
#include <iostream>


AddLogic::AddLogic(FileLogic fileHandler) : fileHandler("")
{
	this->fileHandler = fileHandler;
	string creationDate = FileEntryFormatter::createAttributedEntry("CreationDate", TimeLogic::getTimeNowInString());
	lineEntry = FileEntryFormatter::addAttributedEntryToLineEntry(creationDate, lineEntry);
}


AddLogic::~AddLogic()
{
}

string AddLogic::getLineEntry()
{
	return lineEntry;
}

void AddLogic::setLineEntry(string newLineEntry)
{
	lineEntry = newLineEntry;
}

void AddLogic::appendToLineEntry(string attribute, string entry)
{
	string attributedEntry = FileEntryFormatter::createAttributedEntry(attribute, entry);
	lineEntry = FileEntryFormatter::addAttributedEntryToLineEntry(attributedEntry, lineEntry);
}

void AddLogic::determineType()
{
	if (FileEntryFormatter::getAttributeEntry("start", lineEntry) == "") {
		if (FileEntryFormatter::getAttributeEntry("end", lineEntry) == "") {
			if (FileEntryFormatter::getAttributeEntry("date", lineEntry) == "") {
				if (FileEntryFormatter::getAttributeEntry("name", lineEntry) == "") {
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
}

bool AddLogic::isDateAndTimeCorrect()
{
	if (FileEntryFormatter::getAttributeEntry("start", lineEntry) == "") {
		if (FileEntryFormatter::getAttributeEntry("end", lineEntry) == "") {
			if (FileEntryFormatter::getAttributeEntry("date", lineEntry) == "") {
				return true;
			}
			else {
				TimeLogic check(FileEntryFormatter::getAttributeEntry("date", lineEntry), "23:59");
				
				return check.getTimeFormatCheck();
			}
		}
		else {
			TimeLogic check(FileEntryFormatter::getAttributeEntry("date", lineEntry), 
				FileEntryFormatter::getAttributeEntry("end", lineEntry));
			
			return check.getTimeFormatCheck();
		}
	}
	else {
		TimeLogic checkStart(FileEntryFormatter::getAttributeEntry("date", lineEntry),
			FileEntryFormatter::getAttributeEntry("start", lineEntry));
		TimeLogic checkEnd(FileEntryFormatter::getAttributeEntry("date", lineEntry),
			FileEntryFormatter::getAttributeEntry("end", lineEntry));
		
		return (checkStart.getTimeFormatCheck() && checkEnd.getTimeFormatCheck()
			&& TimeLogic::isFirstEarlierThanSecond(checkStart,checkEnd));
	}
}
bool AddLogic::isSlotFree() {
	bool slotFree = true;
	string startTime = FileEntryFormatter::getAttributeEntry("start", lineEntry);
	string endTime = FileEntryFormatter::getAttributeEntry("end", lineEntry);
	string date = FileEntryFormatter::getAttributeEntry("date", lineEntry);
	
	if (startTime != "" && endTime != "" && date != "") {
		TimeLogic start(date, startTime);
		TimeLogic end(date, endTime);
		int size = fileHandler.getSize();
		
		for (int i = 0; i < size; ++i) {
			string line = fileHandler.getLineFromPositionNumber(i);
			
			if (FileEntryFormatter::getAttributeEntry("type", line) == "timed") {
				string start2 = FileEntryFormatter::getAttributeEntry("start", line);
				string end2 = FileEntryFormatter::getAttributeEntry("end", line);
				string date2 = FileEntryFormatter::getAttributeEntry("date", line);
				TimeLogic startTime2(date2, start2);
				TimeLogic endTime2(date2, end2);
				
				if (startTime2.getTimeFormatCheck() && endTime2.getTimeFormatCheck()) {
					if (!TimeLogic::isFirstEarlierThanSecond(end,startTime2) &&
						!TimeLogic::isFirstEarlierThanSecond(endTime2, start) &&
						TimeLogic::isFirstEarlierThanSecond(startTime2, endTime2)) {
						slotFree = false;
					}
				}
			}
		}
	}
	return slotFree;
}

bool AddLogic::isEntryValid() 
{
	bool isValid = false;
	if (!isDateAndTimeCorrect) {
		//Time error
		return isValid;
	}
	else {
		determineType();
		string type = FileEntryFormatter::getAttributeEntry("type", lineEntry);
		if (type == "") {
			//format error
			return isValid;
		}
		else {
			if (type == "timed" && !isSlotFree()) {
				//no slots
				return isValid;
			}
			else {
				isValid = true;
				return isValid;
			}
		}
	}
}

void AddLogic::commitAdd()
{
	if (isEntryValid()) {
		appendToLineEntry("complete", "no");
		fileHandler.appendToFile(lineEntry);
	}
}