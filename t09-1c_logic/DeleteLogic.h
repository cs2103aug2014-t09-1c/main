#pragma once
#ifndef DELETE_LOGIC
#define DELETE_LOGIC

#include "BaseClassLogic.h"

#define SLOT_IN_EXCESS \
	"Chosen number(s) out of bounds"

class DeleteLogic :
	public BaseClassLogic
{
private:
	void checkFromToValidity(int fromPosition, int toPosition, int size);
	vector<int> reAdjustPos(vector<int> pos, int deletedPos);
	void storeOldEntryForUndo(int filePosition);

public:
	DeleteLogic(string fileName, string date, vector<string> keywords, int displayCase);
	DeleteLogic(vector<string> testVector, string date, vector<string> keywords, int displayCase);
	~DeleteLogic();

	void execute(map<string, int> fromToPositions);
};

#endif

