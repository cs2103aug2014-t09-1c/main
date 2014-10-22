#pragma once
#ifndef DELETE_LOGIC
#define DELETE_LOGIC

#include "BaseClassLogic.h"
#include "ArrangeLogic.h"
#include <stack>


class DeleteLogic :
	public BaseClassLogic
{
private:
	FileLogic fileHandler;
	int displayCase;

public:
	DeleteLogic(string fileName, int displayCase);
	~DeleteLogic();

	stack<string> deletedEntry;
	stack<int> deletedPosition;

	void deleteEntry(string date, int position);
};

#endif

