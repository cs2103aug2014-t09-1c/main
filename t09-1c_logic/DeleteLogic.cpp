#include "stdafx.h"
#include "DeleteLogic.h"
#include <string>

DeleteLogic::DeleteLogic(string fileName) : fileHandler(fileName)
{
}


DeleteLogic::~DeleteLogic()
{
}

void DeleteLogic::deleteEntry(string date, int position) 
{
	ArrangeLogic arranger(fileHandler);
	pair<vector<string>, vector<int>> list = arranger.getListOfEventOn(date);
	vector<string> lines = list.first;
	vector<int> positions = list.second;
	int positionSize = positions.size();
	if (position - 1 < positionSize) {
		deletedEntry = lines[position - 1];
		deletedPosition = positions[position - 1];
		fileHandler.deleteLine(deletedPosition);
	}

}
