#include "stdafx.h"
#include "AddLogic.h"

AddLogic::AddLogic(string fileName) try : BaseClassLogic(fileName)
{
}

catch (const exception& ex)
{
	throw runtime_error(ex.what());
}

AddLogic::AddLogic(vector<string> testVector) : BaseClassLogic(testVector)
{
}

AddLogic::~AddLogic()
{
}

string AddLogic::getLineEntry()
{
	return lineEntry;
}

void AddLogic::appendToLineEntry(string attribute, string entry)
{
	string attributedEntry = createAttributedEntry(attribute, entry);
	lineEntry = addAttributedEntryToLineEntry(attributedEntry, lineEntry);
}

void AddLogic::determineType()
{
	bool isNameEmpty = getAttributeEntry(NAME_ATTRIBUTE, lineEntry) == "";
	bool isDateEmpty = getAttributeEntry(DATE_ATTRIBUTE, lineEntry) == "";
	bool isStartTimeEmpty = getAttributeEntry(START_ATTRIBUTE, lineEntry) == "";
	bool isEndTimeEmpty = getAttributeEntry(END_ATTRIBUTE, lineEntry) == "";
	
	if (isStartTimeEmpty) {
		if (isEndTimeEmpty) {
			if (isDateEmpty) {
				if (isNameEmpty) {
				}
				else {
					appendToLineEntry(TYPE_ATTRIBUTE, "float");
				}
			}
			else {
				lineEntry = editAttributedEntryFromLineEntry(END_ATTRIBUTE, "23:59", lineEntry);
				appendToLineEntry(TYPE_ATTRIBUTE, "deadline");
			}
		}
		else {
			appendToLineEntry(TYPE_ATTRIBUTE, "deadline");
		}
	}
	else {
		appendToLineEntry(TYPE_ATTRIBUTE, "timed");
	}
}

void AddLogic::addCompleteEntry()
{
	appendToLineEntry(COMPLETE_ATTRIBUTE, "no");
}

void AddLogic::validChecks() 
{
	if (!isDateAndTimeCorrect(lineEntry)) {
		throw runtime_error(ADD_LOGIC_TIME_DATE_ERROR);
	}
	else {
		determineType();
		string type = getAttributeEntry(TYPE_ATTRIBUTE, lineEntry);
		if (type == "") {
			throw runtime_error(ADD_LOGIC_MISSING_ERROR);
		}
	}
}

void AddLogic::execute(map<string,string> lineEntries)
{
	appendToLineEntry(CREATION_ATTRIBUTE, getTimeNowInString());
	appendToLineEntry(NAME_ATTRIBUTE, lineEntries[NAME_ATTRIBUTE]);
	appendToLineEntry(DATE_ATTRIBUTE, lineEntries[DATE_ATTRIBUTE]);
	appendToLineEntry(START_ATTRIBUTE, lineEntries[START_ATTRIBUTE]);
	appendToLineEntry(END_ATTRIBUTE, lineEntries[END_ATTRIBUTE]);
	appendToLineEntry(CATEGORY_ATTRIBUTE, lineEntries[CATEGORY_ATTRIBUTE]);
	addCompleteEntry();

	try{
		validChecks();
		appendToFile(lineEntry);
		if (isTestMode) {
			updateSortedEntries();
		}
	}
	catch (const exception& ex) {
		throw runtime_error(ex.what());
	}
}