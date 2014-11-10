//@author A0116410Y
#include "stdafx.h"
#include "DeleteLogic.h"

DeleteLogic::DeleteLogic(string fileName, string date, vector<string> keywords, int displayCase) try : BaseClassLogic(fileName, date, keywords, displayCase)
{
}

catch (const exception& ex)
{
	throw runtime_error(ex.what());
}

DeleteLogic::DeleteLogic(vector<string> testVector, string date, vector<string> keywords, int displayCase) : BaseClassLogic(testVector, date, keywords, displayCase)
{
}

DeleteLogic::~DeleteLogic()
{
}

void DeleteLogic::checkFromToValidity(int fromPosition, int toPosition, int size)
{
	if (fromPosition >= size || fromPosition < 0 || toPosition >= size || toPosition < 0) {
		throw runtime_error(SLOT_IN_EXCESS);
	}
}

vector<int> DeleteLogic::reAdjustPos(vector<int> pos, int deletedPos)
{
	vector<int> positions = pos;
	int posSize = positions.size();
	for (int i = 0; i < posSize; ++i) {
		if (positions[i] > deletedPos) {
			--positions[i];
		}
		//toLog("New Pos: " + positions[i]);
	}
	return positions;
}

void DeleteLogic::execute(map<string, int> fromToPositions)
{
	vector<int> positions = getSortedLinePositions();
	int positionSize = getSortedLinePositions().size();
	int startPosition = fromToPositions[FROM_POSITION] - 1;
	int toPosition = fromToPositions[TO_POSITION] - 1;
	try {
		checkFromToValidity(startPosition, toPosition, positionSize);
		for (int i = toPosition; i >= startPosition; --i) {
			int filePosition = positions[i];
			storeOldEntryForUndo(filePosition);
			string line = getLineFromPositionNumber(filePosition);
			deleteLine(filePosition);
			positions = reAdjustPos(positions, filePosition);
		}
		if (isTestMode) {
			updateSortedEntries();
		}
	}
	catch (const exception& ex) {
		throw runtime_error(ex.what());
	}
}

void DeleteLogic::storeOldEntryForUndo(int filePosition)
{
	oldLinePosforUndo.push(filePosition);
	string line = getLineFromPositionNumber(filePosition);
	OldLineEntriesForUndo.push(line);
}