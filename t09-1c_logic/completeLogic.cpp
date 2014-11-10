#include "stdafx.h"
#include "CompleteLogic.h"

CompleteLogic::CompleteLogic(string fileName, string date, vector<string> keywords, int displayCase) try : BaseClassLogic(fileName, date, keywords, displayCase)
{
}

catch (const exception& ex)
{
	throw runtime_error(ex.what());
}

CompleteLogic::CompleteLogic(vector<string> testVector, string date, vector<string> keywords, int displayCase) : BaseClassLogic(testVector, date, keywords, displayCase)
{
}

CompleteLogic::~CompleteLogic()
{
}

void CompleteLogic::editCompletion(int fromPosition, int toPosition, bool complete)
{
	vector<int> positions = getSortedLinePositions();
	int positionSize = positions.size();
	int startPosition = fromPosition - 1;
	int endPosition = toPosition - 1;
	try {
		checkFromToValidity(startPosition, endPosition, positionSize);
		for (int i = startPosition; i <= endPosition; ++i) {
			int filePosition = positions[i];
			storeOldEntryForUndo(filePosition);
			string line = getLineFromPositionNumber(filePosition);
			if (complete) {
				line = editAttributedEntryFromLineEntry(COMPLETE_ATTRIBUTE, TASK_COMPLETE, line);
			}
			else {
				line = editAttributedEntryFromLineEntry(COMPLETE_ATTRIBUTE, TASK_NOT_COMPLETE, line);
			}
			editLine(filePosition, line);
		}
	}
	catch (const exception& ex) {
		throw runtime_error(ex.what());
	}
}

void CompleteLogic::storeOldEntryForUndo(int filePosition)
{
	oldLinePosforUndo.push(filePosition);
	string line = getLineFromPositionNumber(filePosition);
	OldLineEntriesForUndo.push(line);
}

void CompleteLogic::checkFromToValidity(int fromPosition, int toPosition, int size)
{
	if (fromPosition >= size || fromPosition < 0 || toPosition >= size || toPosition < 0) {
		throw runtime_error(SLOT_IN_EXCESS);
	}
}

void CompleteLogic::execute(map<string, int> fromToPositions, int executionCase)
{
	try {
		if (executionCase == COMPLETE) {
			editCompletion(fromToPositions[FROM_POSITION], fromToPositions[TO_POSITION], true);
		}
		else if (executionCase == UNCOMPLETE) {
			editCompletion(fromToPositions[FROM_POSITION], fromToPositions[TO_POSITION], false);
		}
		else {
			assert(false && "Wrong execution case inserted.");
		}
		if (isTestMode) {
			updateSortedEntries();
		}
	}
	catch (const exception& ex) {
		throw runtime_error(ex.what());
	}
}