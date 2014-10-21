#include "stdafx.h"
#include "CompleteLogic.h"
#include <string>

CompleteLogic::CompleteLogic(string fileName, int displayCase) : fileHandler(fileName)
{
	this->displayCase = displayCase;
}


CompleteLogic::~CompleteLogic()
{
}

void CompleteLogic::CompleteTask(string date, int position)
{
	ArrangeLogic arranger(fileHandler);
	pair<vector<string>, vector<int>> list;
	if (displayCase == 0) {
		list = arranger.getListOfEventsOnwardFrom(date);
	}
	else {
		list = arranger.getListOfEventOn(date);
	}

	vector<string> lines = list.first;
	vector<int> positions = list.second;

	int positionSize = positions.size();
	if (position - 1 < positionSize) {
		taskCompleted = lines[position - 1];
		completedTaskPosition = positions[position - 1];
		//fileHandler.appendCompletedMarkToTask(completeTaskPosition);
	}

	string lineText = FileLogic::getLineFromPositionNumber(int completedTaskPosition);
	void EditLogic::appendEntry(string status, string completed);
}