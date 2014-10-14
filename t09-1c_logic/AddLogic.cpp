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
	bool isNameEmpty = FileEntryFormatter::getAttributeEntry("name", lineEntry) == "";
	bool isDateEmpty = FileEntryFormatter::getAttributeEntry("date", lineEntry) == "";
	bool isStartTimeEmpty = FileEntryFormatter::getAttributeEntry("start", lineEntry) == "";
	bool isEndTimeEmpty = FileEntryFormatter::getAttributeEntry("end", lineEntry) == "";
	
	if (isStartTimeEmpty) {
		if (isEndTimeEmpty) {
			if (isDateEmpty) {
				if (isNameEmpty) {
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
	appendToLineEntry("complete", "no");
}

bool AddLogic::isDateAndTimeCorrect()
{
	string date = FileEntryFormatter::getAttributeEntry("date", lineEntry);
	string startTime = FileEntryFormatter::getAttributeEntry("start", lineEntry);
	string endTime = FileEntryFormatter::getAttributeEntry("end", lineEntry);

	if (startTime.empty()) {
		if (endTime.empty()) {
			if (date.empty()) {
				return true;
			}
			else {
				TimeLogic check(date, "23:59");
				return check.getTimeFormatCheck();
			}
		}
		else {
			TimeLogic check(date, endTime);
			return check.getTimeFormatCheck();
		}
	}
	else {
		TimeLogic checkStart(date, startTime);
		TimeLogic checkEnd(date, endTime);
		
		return (checkStart.getTimeFormatCheck() && checkEnd.getTimeFormatCheck()
			&& TimeLogic::isFirstEarlierThanSecond(checkStart,checkEnd) &&
			startTime != endTime);
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
					if (date == date2 && startTime == start2 && endTime == end2) {
						slotFree = false;
						break;
					}

					if (startTime != start2 && startTime != end2) {
						if (TimeLogic::isFirstEarlierThanSecond(startTime2, start) &&
							TimeLogic::isFirstEarlierThanSecond(start, endTime2)) {
							slotFree = false;
							break;
						}
					}

					if (endTime != start2 && endTime != end2) {
						if (TimeLogic::isFirstEarlierThanSecond(startTime2, end) &&
							TimeLogic::isFirstEarlierThanSecond(end, endTime2)) {
							slotFree = false;
							break;
						}
					}
					
					if (endTime != start2 && startTime != start2) {
						if (TimeLogic::isFirstEarlierThanSecond(start, startTime2) &&
							TimeLogic::isFirstEarlierThanSecond(startTime2, end)) {
							slotFree = false;
							break;
						}
					}

					if (endTime != end2 && startTime != end2) {
						if (TimeLogic::isFirstEarlierThanSecond(start, endTime2) &&
							TimeLogic::isFirstEarlierThanSecond(endTime2, end)) {
							slotFree = false;
							break;
						}
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
	if (!isDateAndTimeCorrect()) {
		//Time error: Invalid date and time. Please refer to \"help\" for guide to input.
		return isValid;
	}
	else {
		determineType();
		string type = FileEntryFormatter::getAttributeEntry("type", lineEntry);
		if (type == "") {
			//format error: No event detected. Please refer to \"help\" for guide to input.
			return isValid;
		}
		else {
			if (type == "timed" && !isSlotFree()) {
				//no slots: No slots are available. Please refer to \"help\" for guide to input.
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

		fileHandler.appendToFile(lineEntry);
	}
}