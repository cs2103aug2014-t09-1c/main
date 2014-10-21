#pragma once
#ifndef ADD_LOGIC
#define ADD_LOGIC

#include "BaseClassLogic.h"

#define ADD_LOGIC_TIME_DATE_ERROR \
	"Please enter a valid DDMMYY date and HHMM time!"
#define ADD_LOGIC_MISSING_ERROR \
	"Please enter at least a name, a date, a start time or an end time!"
#define ADD_LOGIC_NO_SLOT_ERROR \
	"The timeslot is occupied!"


class AddLogic :
	public BaseClassLogic
{
private:
	string lineEntry;

	FileLogic fileHandler;
	string error;
	string errorPresent;


public:
	string error;
	AddLogic(string fileName);
	~AddLogic();
	string getLineEntry();
	void setLineEntry(string newLineEntry);
	bool isDateAndTimeCorrect();
	bool isSlotFree();
	void appendToLineEntry(string attribute, string entry);
	void determineType();
	void setErrorString(string errorString);
	string getErrorString();
	bool isEntryValid();
	void commitAdd();
	string errorMsg;
};

#endif
