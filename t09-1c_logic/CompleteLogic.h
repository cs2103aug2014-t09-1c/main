#pragma once
#include "BaseClassLogic.h"
#include "ArrangeLogic.h"
#include "FileLogic.h"
#include <stack>

class CompleteLogic :
	public BaseClassLogic
{

private:
	FileLogic fileHandler;
	int displayCase;

	void completer(string date, int fromPosition, int toPosition, bool complete);

public:
	CompleteLogic(string fileName, int displayCase);
	~CompleteLogic();
	
	stack<int> fileEntryPositions;
	string commandType;

	void complete(string date, int fromPosition, int toPosition);
	void uncomplete(string date, int fromPosition, int toPosition);


};
