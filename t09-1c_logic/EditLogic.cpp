#include "stdafx.h"
#include "EditLogic.h"

EditLogic::EditLogic(string fileName, string date, vector<string> keywords, int displayCase) try : BaseClassLogic(fileName, date, keywords, displayCase)
{
}

catch (const exception& ex)
{
	throw runtime_error(ex.what());
}

EditLogic::EditLogic(vector<string> testVector, string date, vector<string> keywords, int displayCase) : BaseClassLogic(testVector, date, keywords, displayCase)
{
}

EditLogic::~EditLogic()
{
}

void EditLogic::redetermineType()
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
					editAttributedEntryFromLineEntry(TYPE_ATTRIBUTE, "float", lineEntry);
				}
			}
			else {
				lineEntry = editAttributedEntryFromLineEntry(END_ATTRIBUTE, "23:59", lineEntry);
				editAttributedEntryFromLineEntry(TYPE_ATTRIBUTE, "deadline", lineEntry);
			}
		}
		else {
			editAttributedEntryFromLineEntry(TYPE_ATTRIBUTE, "deadline", lineEntry);
		}
	}
	else {
		editAttributedEntryFromLineEntry(TYPE_ATTRIBUTE, "timed", lineEntry);
	}
}

void EditLogic::resetCompletion()
{
	editAttributedEntryFromLineEntry(COMPLETE_ATTRIBUTE, "no", lineEntry);
}

void EditLogic::editValidChecks()
{
	if (!isDateAndTimeCorrect(lineEntry)) {
		throw runtime_error(EDIT_LOGIC_TIME_DATE_ERROR);
	}
	else {
		redetermineType();
		string type = getAttributeEntry(TYPE_ATTRIBUTE, lineEntry);
		if (type == "") {
			throw runtime_error(EDIT_LOGIC_MISSING_ERROR);
		}
	}
}

void EditLogic::checkPosValidity(int position, int size)
{
	if (position >= size || position < 0) {
		throw runtime_error(EDIT_SLOT_EXCESS_ERROR);
	}
}

void EditLogic::editEntries(map<string, string> lineEntries)
{
	lineEntry = editAttributedEntryFromLineEntry(NAME_ATTRIBUTE, lineEntries[NAME_ATTRIBUTE], lineEntry);
	lineEntry = editAttributedEntryFromLineEntry(DATE_ATTRIBUTE, lineEntries[DATE_ATTRIBUTE], lineEntry);
	lineEntry = editAttributedEntryFromLineEntry(START_ATTRIBUTE, lineEntries[START_ATTRIBUTE], lineEntry);
	lineEntry = editAttributedEntryFromLineEntry(END_ATTRIBUTE, lineEntries[END_ATTRIBUTE], lineEntry);
	lineEntry = editAttributedEntryFromLineEntry(CATEGORY_ATTRIBUTE, lineEntries[CATEGORY_ATTRIBUTE], lineEntry);
}

void EditLogic::execute(map<string, int> position, map<string, string> lineEntries)
{
	int intPos = position[FROM_POSITION];
	int pos = intPos - 1;
	vector<int> positions = getSortedLinePositions();
	int size = positions.size();
	try {
		checkPosValidity(pos, size);
		int filePosition = positions[pos];
		oldLinePosforUndo.push(filePosition);
		lineEntry = getLineFromPositionNumber(filePosition);
		OldLineEntriesForUndo.push(lineEntry);
		editEntries(lineEntries);
		resetCompletion();
		editValidChecks();
		editLine(filePosition, lineEntry);
		if (isTestMode) {
			updateSortedEntries();
		}
	}
	catch (const exception& ex) {
		throw runtime_error(ex.what());
	}
}