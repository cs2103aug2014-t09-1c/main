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

pair<vector<string>, vector<int>> ArrangeLogic::getListOfEventOn(string date)
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
			pair<vector<string>, vector<int>> addedPair = addNonFloatEventToEntry(lineEntry, linePosition, i);
			lineEntry = addedPair.first;
			linePosition = addedPair.second;
		}
	}
	pair<vector<string>, vector<int>> list(lineEntry, linePosition);
	return list;
}

pair<vector<string>, vector<int>> ArrangeLogic::getListOfEventsOnwardFrom(string date)
{
	vector<string> lineEntry;
	vector<int> linePosition;

	int size = fileHandler.getSize();

	TimeLogic dateQualifier(date, "00:00");

	for (int i = 0; i < size; ++i) {
		string line = fileHandler.getLineFromPositionNumber(i);
		if (FileEntryFormatter::getAttributeEntry("type", line) == "float") {
			lineEntry.push_back(line);
			linePosition.push_back(i);
		}
		else {
			string lineDateString = FileEntryFormatter::getAttributeEntry("date", line);
			TimeLogic lineDate(lineDateString, "00:00");
			
			if (lineDate.getTimeFormatCheck()) {
				if (TimeLogic::isFirstEarlierThanSecond(dateQualifier, lineDate)) {
					pair<vector<string>, vector<int>> addedPair = addNonFloatEventToEntry(lineEntry, linePosition, i);
					lineEntry = addedPair.first;
					linePosition = addedPair.second;
				}
			}
		}
	}
	pair<vector<string>, vector<int>> list(lineEntry, linePosition);
	return list;
}

TimeLogic ArrangeLogic::getPriorityDateTime(string line)
{
	string lineDate = FileEntryFormatter::getAttributeEntry("date", line);
	string lineTime;
	if (FileEntryFormatter::getAttributeEntry("type", line) == "deadline") {
		lineTime = FileEntryFormatter::getAttributeEntry("end", line);
	}
	else if (FileEntryFormatter::getAttributeEntry("type", line) == "timed") {
		lineTime = FileEntryFormatter::getAttributeEntry("start", line);
	}
	TimeLogic priorityDateTime(lineDate, lineTime);

	return priorityDateTime;
}

pair<vector<string>, vector<int>> ArrangeLogic::addNonFloatEventToEntry(vector<string> lineEntry, vector<int> linePosition, int iteration)
{
	string line = fileHandler.getLineFromPositionNumber(iteration);

	if (lineEntry.size() == 0) {
		lineEntry.push_back(line);
		linePosition.push_back(iteration);
	}
	else {
		vector<string>::iterator it1 = lineEntry.begin();
		vector<int>::iterator it2 = linePosition.begin();
		int minSize = 0;
		int maxSize = lineEntry.size() -1;
		
		while (maxSize >= minSize) {
			int mid = (minSize + maxSize) / 2;
			string checkLine = lineEntry[mid];

			if (FileEntryFormatter::getAttributeEntry("type", checkLine) == "float") {
				if (maxSize == minSize) {
					lineEntry.insert(it1 + minSize, line);
					linePosition.insert(it2 + minSize, iteration);
					break;
				}
				else {
					maxSize = mid;
				}
			}

			TimeLogic checkLineTimeLogic = getPriorityDateTime(checkLine);
			TimeLogic deadline = getPriorityDateTime(line);

			if (TimeLogic::isFirstEarlierThanSecond(deadline, checkLineTimeLogic)) {
				if (maxSize == minSize) {
					lineEntry.insert(it1 + minSize, line);
					linePosition.insert(it2 + minSize, iteration);
					break;
				}
				else {
					maxSize = mid;
				}
			}

			else {
				if (minSize == maxSize) {
					lineEntry.push_back(line);
					linePosition.push_back(iteration);
					break;
				}
				else {
					minSize = mid + 1;
				}
			}
		}
	}
	pair<vector<string>, vector<int>> list(lineEntry, linePosition);
	return list;
}