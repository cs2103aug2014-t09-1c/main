#include "stdafx.h"
#include "ArrangeLogic.h"
#include "TimeLogic.h"
#include "FileLogic.h"
#include "FileEntryFormatter.h"

ArrangeLogic::ArrangeLogic(FileLogic fileHandler) : fileHandler("")
{
	this->fileHandler = fileHandler;
}


ArrangeLogic::~ArrangeLogic()
{
}

pair<vector<string>, vector<int>> ArrangeLogic::getListOfDate(string date)
{
	vector<string> lineEntry;
	vector<int> linePosition;

	int size = fileHandler.getSize();

	for (int i = 0; i < size; ++i) {
		string line = fileHandler.getLineFromPositionNumber(i);
		if (FileEntryFormatter::getAttributeEntry("type", line) == "float") {
			lineEntry.push_back(line);
			linePosition.push_back(i);
		}
		else if (FileEntryFormatter::getAttributeEntry("date", line) == date) {
			if (lineEntry.size() == 0) {
				lineEntry.push_back(line);
				linePosition.push_back(i);
			}
			else {
				vector<string>::iterator it1 = lineEntry.begin();
				vector<int>::iterator it2 = linePosition.begin();
				int iterator = 0;
				int size2 = lineEntry.size();
				while (iterator < size2) {
					string checkLine = lineEntry[iterator];
					if (FileEntryFormatter::getAttributeEntry("type", checkLine) == "float") {
						lineEntry.insert(it1 + iterator, line);
						linePosition.insert(it2 + iterator, i);
						break;
					}

					string checkLineDate = FileEntryFormatter::getAttributeEntry("date", checkLine);
					string checkLineTime;
					if (FileEntryFormatter::getAttributeEntry("type", checkLine) == "deadline") {
						string checkLineTime = FileEntryFormatter::getAttributeEntry("end", checkLine);
					}
					else if (FileEntryFormatter::getAttributeEntry("type", checkLine) == "timed") {
						string checkLineTime = FileEntryFormatter::getAttributeEntry("start", checkLine);
					}
					TimeLogic checkLineTimeLogic(checkLineDate, checkLineTime);

					string lineDate = FileEntryFormatter::getAttributeEntry("date", line);
					string lineTime;
					if (FileEntryFormatter::getAttributeEntry("type", line) == "deadline") {
						string lineTime = FileEntryFormatter::getAttributeEntry("end", line);
					}
					else if (FileEntryFormatter::getAttributeEntry("type", line) == "timed") {
						string lineTime = FileEntryFormatter::getAttributeEntry("start", line);
					}
					TimeLogic deadline(lineDate, lineTime);

					if (TimeLogic::isFirstEarlierThanSecond(deadline, checkLineTimeLogic)) {
						lineEntry.insert(it1 + iterator, line);
						linePosition.insert(it2 + iterator, i);
						break;
					}
					else {
						++iterator;
					}
				}
			}
		}
	}
	pair<vector<string>, vector<int>> list(lineEntry, linePosition);
	return list;
}
