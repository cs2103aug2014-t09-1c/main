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

	if (isStartTimeEmpty && isEndTimeEmpty && isDateEmpty && isNameEmpty) {
		//do nothing
	}
	else if (isStartTimeEmpty && isEndTimeEmpty && isDateEmpty) {
		appendToLineEntry(TYPE_ATTRIBUTE, FLOAT_TASK_TYPE);
	}
	else if (isStartTimeEmpty && isEndTimeEmpty) {
		lineEntry = editAttributedEntryFromLineEntry(END_ATTRIBUTE, END_OF_DAY_TIME, lineEntry);
		appendToLineEntry(TYPE_ATTRIBUTE, DEADLINE_TASK_TYPE);
	}
	else if (isStartTimeEmpty) {
		appendToLineEntry(TYPE_ATTRIBUTE, DEADLINE_TASK_TYPE);
	}
	else {
		appendToLineEntry(TYPE_ATTRIBUTE, TIMED_TASK_TYPE);
	}
}

void AddLogic::addCompleteEntry()
{
	appendToLineEntry(COMPLETE_ATTRIBUTE, TASK_NOT_COMPLETE);
}

void AddLogic::validChecks() 
{
	determineType();
	if (!isDateAndTimeCorrect(lineEntry)) {
		throw runtime_error(ADD_LOGIC_TIME_DATE_ERROR);
	}
	else {
		string type = getAttributeEntry(TYPE_ATTRIBUTE, lineEntry);
		if (type == "") {
			throw runtime_error(ADD_LOGIC_MISSING_ERROR);
		}
	}
}

void AddLogic::execute(map<string,string> lineEntries)
{
	if (!isTestMode) {
		appendToLineEntry(CREATION_ATTRIBUTE, getTimeNowInString());
	}
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