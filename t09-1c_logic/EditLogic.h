//@author A0116410Y
#pragma once
#ifndef EDIT_LOGIC
#define EDIT_LOGIC

#include "BaseClassLogic.h"

#define EDIT_LOGIC_TIME_DATE_ERROR \
	"Please enter a valid DDMMYY date and HHMM time!"
#define EDIT_LOGIC_MISSING_ERROR \
	"Please enter at least a name, a date, a start time or an end time!"
#define EDIT_SLOT_EXCESS_ERROR \
	"Edit Failed. Selected number is out of bounds."

class EditLogic :
	public BaseClassLogic
{
private:
	string lineEntry;

	/*
	*Re-Determines the type of the event to be added if it is either
	*a deadline, timed or float task. This should only be run after all entries are edited.
	*/
	void redetermineType();
	/*
	*Resets the completion to Not completed
	*/
	void resetCompletion();
	void editValidChecks();
	void checkPosValidity(int position, int size);
	void editEntries(map<string, string> lineEntries);

public:
	EditLogic(string fileName, string date, vector<string> keywords, int displayCase);
	EditLogic(vector<string> testVector, string date, vector<string> keywords, int displayCase);
	~EditLogic();

	void execute(map<string, int> position, map<string, string> lineEntries);
	
	string getLineEntry();
};

#endif

