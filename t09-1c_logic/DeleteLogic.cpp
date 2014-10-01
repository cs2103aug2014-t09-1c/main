#include "stdafx.h"
#include "DeleteLogic.h"
#include <string>

DeleteLogic::DeleteLogic(string fileName) : arranger(fileName), fileHandler(fileName)
{
}


DeleteLogic::~DeleteLogic()
{
}

void DeleteLogic::deleteEntry(string date, int position) 
{
	pair<vector<string>, vector<int>> list = arranger.getListOfDate(date);
	vector<int> positions = list.second;
	if (position - 1 < positions.size()) {
		fileHandler.deleteLine(positions[position - 1]);
	}

}
