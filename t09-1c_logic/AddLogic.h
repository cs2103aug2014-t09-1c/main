#pragma once
#ifndef ADD_LOGIC
#define ADD_LOGIC

#include "BaseClassLogic.h"

#define ADD_LOGIC_TIME_DATE_ERROR \
	"Please enter a valid DDMMYY date and HHMM time!"
#define ADD_LOGIC_MISSING_ERROR \
	"Please enter at least a name, a date, a start time or an end time!"

class AddLogic :
	public BaseClassLogic
{
private:
	string lineEntry;
	void appendToLineEntry(string attribute, string entry);
	void determineType();
	void addCompleteEntry();
	void validChecks();

public:
	AddLogic(string fileName);
	AddLogic(vector<string> testVector);
	~AddLogic();

	//This method must only be used in automated Testing purposes.
	string getLineEntry();
	
	void execute(map<string, string> lineEntries);
};

#endif
