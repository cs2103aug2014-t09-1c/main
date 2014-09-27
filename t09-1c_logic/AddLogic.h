#pragma once
#ifndef ADD_LOGIC
#define ADD_LOGIC

#include "BaseClassLogic.h"
class AddLogic :
	public BaseClassLogic
{
private:
	string lineEntry;
	int positionToPlace;

public:
	AddLogic();
	~AddLogic();
	void appendToLineEntry(string attribute, string entry);
	void determinePositionInFile();
	void commitAdd();

};

#endif
