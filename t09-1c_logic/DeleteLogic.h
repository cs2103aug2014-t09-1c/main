#pragma once
#ifndef DELETE_LOGIC
#define DELETE_LOGIC
#include "BaseClassLogic.h"
#include "ArrangeLogic.h"


class DeleteLogic :
	public BaseClassLogic
{
private:
	FileLogic fileHandler;
	int displayCase;

public:
	DeleteLogic(string fileName, int displayCase);
	~DeleteLogic();

	string deletedEntry;
	int deletedPosition = -1;

	void deleteEntry(string date, int position);
};

#endif

