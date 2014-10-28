#include "stdafx.h"
#include "CompleteLogic.h"
#include <string>
#include "FileEntryFormatter.h"

CompleteLogic::CompleteLogic(string fileName, int displayCase) : fileHandler(fileName)
{
	this->displayCase = displayCase;
}


CompleteLogic::~CompleteLogic()
{
}

void CompleteLogic::completer(string date, vector<string> keywords, int fromPosition, int toPosition, bool complete)
{
	ArrangeLogic arranger(fileHandler);
	pair<vector<string>, vector<int>> list;
	switch (displayCase) {
	case 0: list = arranger.getListOfEventsOnwardFrom(date);
		break;
	default: list = arranger.getListOfEventsWithKeywords(keywords);
		break;
	}
	vector<int> positions = list.second;
	int positionSize = positions.size();
	for (int i = fromPosition -1; i <= toPosition -1 && i <= positionSize; ++i)
	{
		int filePosition = positions[i];
		fileEntryPositions.push(filePosition);
		string line = fileHandler.getLineFromPositionNumber(filePosition);
		originalFileEntries.push(line);
		if (complete) {
			line = FileEntryFormatter::editAttributedEntryFromLineEntry("complete", "yes", line);
		}
		else {
			line = FileEntryFormatter::editAttributedEntryFromLineEntry("complete", "no", line);
		}
		fileHandler.deleteLine(filePosition);
		fileHandler.addToPositionNumber(filePosition, line);
	}
}

void CompleteLogic::complete(string date, vector<string> keywords, int fromPosition, int toPosition)
{
	commandType = "complete";
	completer(date, keywords, fromPosition, toPosition, true);
}

void CompleteLogic::uncomplete(string date, vector<string> keywords, int fromPosition, int toPosition)
{
	commandType = "uncomplete";
	completer(date, keywords, fromPosition, toPosition, false);
}