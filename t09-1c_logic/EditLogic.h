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
	AddLogic addFunction;

public:
	EditLogic(FileLogic fileHandler);
	~EditLogic();

	void appendEntry(string attriibute, string entry);
	void editEntry(string date, int position);
};

#endif

