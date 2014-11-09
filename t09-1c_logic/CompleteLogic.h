#pragma once
#ifndef COMPLETE_LOGIC
#define COMPLETE_LOGIC

#include "BaseClassLogic.h"

#define SLOT_IN_EXCESS \
	"Chosen number(s) out of bounds"

class CompleteLogic :
	public BaseClassLogic
{

private:
	void editCompletion(int fromPosition, int toPosition, bool complete);
	void checkFromToValidity(int fromPosition, int toPosition, int size);
	void storeOldEntryForUndo(int filePosition);

public:
	CompleteLogic(string fileName, string date, vector<string> keywords, int displayCase);
	CompleteLogic(vector<string> testVector, string date, vector<string> keywords, int displayCase);
	~CompleteLogic();

	void execute(map<string, int> fromToPositions, int executionCase);
	
	stack<string> getLinesForUndo();
	stack<int> getPosForUndo();

};
#endif
