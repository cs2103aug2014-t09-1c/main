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

public:
	DeleteLogic(string fileName);
	~DeleteLogic();

	string deletedEntry;
	int deletedPosition = -1;

	void deleteEntry(string date, int position);
};

#endif

