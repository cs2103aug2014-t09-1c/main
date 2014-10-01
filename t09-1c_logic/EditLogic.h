#pragma once
#ifndef EDIT_LOGIC
#define EDIT_LOGIC

#include "BaseClassLogic.h"
#include "ArrangeLogic.h"

class EditLogic :
	public BaseClassLogic
{
private:
	FileLogic fileHandler;
	ArrangeLogic arranger;

public:
	EditLogic();
	~EditLogic();

	void editEntry(string date, string position);
};

#endif

