#pragma once
#ifndef ADD_LOGIC
#define ADD_LOGIC

#include "BaseClassLogic.h"

class AddLogic :
	public BaseClassLogic
{
private:
	string lineEntry;

	FileLogic fileHandler;

public:
	AddLogic(string fileName);
	~AddLogic();
	string getLineEntry();
	bool isDateAndTimeCorrect();
	bool isSlotFree();
	void appendToLineEntry(string attribute, string entry);
	void determineType();
	void commitAdd();

};

#endif
