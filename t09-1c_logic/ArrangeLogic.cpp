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

pair<vector<string>, vector<int>> ArrangeLogic::getAllEntries()
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
		else if (FileEntryFormatter::getAttributeEntry("type", line) != "") {
			pair<vector<string>, vector<int>> addedPair = addNonFloatEventToEntry(lineEntry, linePosition, i);
			lineEntry = addedPair.first;
			linePosition = addedPair.second;
		}
	}
	pair<vector<string>, vector<int>> list(lineEntry, linePosition);
	return list;
}

pair<vector<string>, vector<int>> ArrangeLogic::getListOfEventsWithKeywords(vector<string> keywords)
{
	vector<string> lineEntry;
	vector<int> linePosition;

	int size = fileHandler.getSize();

	for (int i = 0; i < size; ++i) {
		string line = fileHandler.getLineFromPositionNumber(i);
		if (checkKeywordCriteria(line, keywords)) {
			if (FileEntryFormatter::getAttributeEntry("type", line) == "float") {
				lineEntry.push_back(line);
				linePosition.push_back(i);
			}
			else if (FileEntryFormatter::getAttributeEntry("type", line) != "") {
				pair<vector<string>, vector<int>> addedPair = addNonFloatEventToEntry(lineEntry, linePosition, i);
				lineEntry = addedPair.first;
				linePosition = addedPair.second;
			}
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
			else {

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
	}
	pair<vector<string>, vector<int>> list(lineEntry, linePosition);
	return list;
}

bool ArrangeLogic::checkKeywordCriteria(string line, vector<string> keywords)
{
	bool isCriteriaMet = false;
	int numKeywords = keywords.size();
	for (int i = 0; i < numKeywords; ++i) {
		string keyword = keywords[i];
		bool isMatchName = FileEntryFormatter::getAttributeEntry("name", line) == keyword;
		if (isMatchName) {
			isCriteriaMet = true;
			break;
		}
		bool isMatchCategory = FileEntryFormatter::getAttributeEntry("category", line) == keyword;
		if (isMatchCategory) {
			isCriteriaMet = true;
			break;
		}
		string lineDate = FileEntryFormatter::getAttributeEntry("date", line);
		TimeLogic date(lineDate, "00:00");
		
		string lineEnd = FileEntryFormatter::getAttributeEntry("end", line);
		TimeLogic endTime(lineDate, lineEnd);

		bool isMatchDate = lineDate == keyword && date.getTimeFormatCheck();
		bool isMatchEndDate = endTime.getStringDate() == keyword && endTime.getTimeFormatCheck();
		if (isMatchDate || isMatchEndDate) {
			isCriteriaMet = true;
			break;
		}
		string lineStart = FileEntryFormatter::getAttributeEntry("start", line);
		TimeLogic startTime(lineDate, lineStart);
		bool isMatchStart = lineStart == keyword && startTime.getTimeFormatCheck();
		if (isMatchStart) {
			isCriteriaMet = true;
			break;
		}

		bool isMatchEnd = endTime.getStringTime() == keyword && endTime.getTimeFormatCheck();
		if (isMatchEnd) {
			isCriteriaMet = true;
			break;
		}
		if (FileEntryFormatter::getAttributeEntry("type", line) == "timed") {
			TimeLogic keywordTime(lineDate, keyword);
			if (TimeLogic::isFirstEarlierThanSecond(startTime, keywordTime) &&
				TimeLogic::isFirstEarlierThanSecond(keywordTime, endTime)) {
				isCriteriaMet = true;
				break;
			}
			if (lineEnd.substr(5, 2) == "+1") {
				TimeLogic keywordTimePlusOne(lineDate, keyword + "+1");
				if (TimeLogic::isFirstEarlierThanSecond(startTime, keywordTimePlusOne) &&
					TimeLogic::isFirstEarlierThanSecond(keywordTimePlusOne, endTime)) {
					isCriteriaMet = true;
					break;
				}
			}
		}
	}
	return isCriteriaMet;
}