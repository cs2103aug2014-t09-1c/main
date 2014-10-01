#pragma once
#ifndef DELETE_LOGIC
#define DELETE_LOGIC
#include "BaseClassLogic.h"
#include "ArrangeLogic.h"


class DeleteLogic :
	public BaseClassLogic
{
private:
	ArrangeLogic arranger;
	FileLogic fileHandler;

public:
	DeleteLogic(FileLogic fileHandler);
	~DeleteLogic();

	string deletedEntry;
	int deletedPosition = -1;

	void deleteEntry(string date, int position);
};

#endif

