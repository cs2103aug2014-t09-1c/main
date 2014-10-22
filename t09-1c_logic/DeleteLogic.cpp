#include "stdafx.h"
#include "DeleteLogic.h"
#include <string>

DeleteLogic::DeleteLogic(string fileName, int displayCase) : fileHandler(fileName)
{
	this->displayCase = displayCase;
}


DeleteLogic::~DeleteLogic()
{
}

void DeleteLogic::deleteEntry(string date, int position) 
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
		deletedEntry.push(lines[position - 1]);
		deletedPosition.push(positions[position - 1]);
		fileHandler.deleteLine(positions[position - 1]);
	}

}
