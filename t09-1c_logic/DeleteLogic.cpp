#include "stdafx.h"
#include "DeleteLogic.h"
#include <string>

DeleteLogic::DeleteLogic(FileLogic fileHandler) : arranger(fileHandler), fileHandler("")
{
	this->fileHandler = fileHandler;
}


DeleteLogic::~DeleteLogic()
{
}

void DeleteLogic::deleteEntry(string date, int position) 
{
	pair<vector<string>, vector<int>> list = arranger.getListOfDate(date);
	vector<string> lines = list.first;
	vector<int> positions = list.second;
	if (position - 1 < positions.size()) {
		deletedEntry = lines[position - 1];
		deletedPosition = positions[position - 1];
		fileHandler.deleteLine(positions[position - 1]);
	}

}
