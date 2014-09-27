#pragma once
#ifndef ADD_LOGIC
#define ADD_LOGIC

#include "BaseClassLogic.h"

class AddLogic :
	public BaseClassLogic
{
private:
	string lineEntry;
	int positionToPlace = 0;

	FileLogic fileHandler;

public:
	AddLogic(string fileName);
	~AddLogic();
	void appendToLineEntry(string attribute, string entry);
	void commitAdd();

};

#endif
