#include "stdafx.h"
#include "DisplayLogic.h"
#include "ArrangeLogic.h"
#include "FileEntryFormatter.h"
#include "TimeLogic.h"



DisplayLogic::DisplayLogic(string fileName) : fileHandler(fileName)
{
}


DisplayLogic::~DisplayLogic()
{
}

vector<string> DisplayLogic::putToVectorEventDatails(string line, bool includeDate, string date)
{
	vector<string> eventVector;
	eventVector.push_back(FileEntryFormatter::getAttributeEntry(DETAIL_AT_POS_0, line));
	eventVector.push_back(FileEntryFormatter::getAttributeEntry(DETAIL_AT_POS_1, line));
	
	string pos2;
	if (FileEntryFormatter::getAttributeEntry(DETAIL_AT_POS_2B, line) != "") {
		if (FileEntryFormatter::getAttributeEntry(DETAIL_AT_POS_2A, line) == date) {
			pos2 = (includeDate ? TODAY : "")
				+ FileEntryFormatter::getAttributeEntry(DETAIL_AT_POS_2B, line);
		}
		else {
			pos2 = (includeDate ? FileEntryFormatter::getAttributeEntry(DETAIL_AT_POS_2A, line) + " " : "")
				+ FileEntryFormatter::getAttributeEntry(DETAIL_AT_POS_2B, line);
		}
	}
	else {
		pos2 = NO_START_STRING;
	}

	string pos3;
	TimeLogic endDate(FileEntryFormatter::getAttributeEntry("date", line),
		FileEntryFormatter::getAttributeEntry("end", line));

	if (endDate.getStringTime() != "") {
		if (endDate.getStringDate() == date) {
			pos3 = (includeDate ? TODAY : "")
				+ endDate.getStringTime();
		}
		else {
			pos3 = (includeDate ? endDate.getStringDate() + " " : "")
				+ endDate.getStringTime();
		}
	}
	else {
		pos2 = FLOAT_START_STRING;
		pos3 = FLOAT_END_STRING;
	}
	eventVector.push_back(pos2);
	eventVector.push_back(pos3);
	eventVector.push_back(FileEntryFormatter::getAttributeEntry(DETAIL_AT_POS_4, line));

	return eventVector;
}

vector<vector<string>> DisplayLogic::collectEventsWithKeywords(vector<string> keywords, string date)
{
	vector<vector<string>> toDisplay;
	ArrangeLogic arranger(fileHandler);
	pair<vector<string>, vector<int>> events = arranger.getListOfEventsWithKeywords(keywords);
	vector<string> eventList = events.first;
	for (size_t i = 0; i < eventList.size(); ++i) {
		vector<string> parsedEvent = putToVectorEventDatails(eventList[i], true, date);
		toDisplay.push_back(parsedEvent);
	}
	return toDisplay;
}

vector<vector<string>> DisplayLogic::collectEventsFromDate(string date)
{
	vector<vector<string>> toDisplay;
	ArrangeLogic arranger(fileHandler);
	pair<vector<string>, vector<int>> events = arranger.getListOfEventsOnwardFrom(date);
	vector<string> eventList = events.first;
	for (size_t i = 0; i < eventList.size(); ++i) {
		vector<string> parsedEvent = putToVectorEventDatails(eventList[i], true, date);
		toDisplay.push_back(parsedEvent);
	}
	return toDisplay;
}

string DisplayLogic::formatContentsToLineEdit(int position, vector<string> keywords, string date, int displayCase)
{
	string lineAppend;
	pair<vector<string>, vector<int>> events;
	ArrangeLogic arranger(fileHandler);
	if (displayCase == 0) {
		events = arranger.getListOfEventsOnwardFrom(date);
	}
	else {
		events = arranger.getListOfEventsWithKeywords(keywords);
	}
	vector<string> eventList = events.first;
	int size = eventList.size();
	if (position <= size) {
		string line = eventList[position - 1];
		string name = FileEntryFormatter::getAttributeEntry("name", line);
		string date = FileEntryFormatter::getAttributeEntry("date", line);
		if (date.length() == 10) {
			date = date.substr(0, 2) + date.substr(3, 2) + date.substr(8, 2);
		}
		string start = FileEntryFormatter::getAttributeEntry("start", line);
		if (start.length() == 5) {
			start = start.substr(0, 2) + start.substr(3, 2);
		}
		string end = FileEntryFormatter::getAttributeEntry("end", line);
		if (end.length() == 5) {
			end = end.substr(0, 2) + end.substr(3, 2);
		}
		else if (end.length() == 7) {
			end = end.substr(0, 2) + end.substr(3, 4);
		}
		string category = FileEntryFormatter::getAttributeEntry("category", line);

		lineAppend = "[" + name + "]" + "[" + date + "]" + "[" + start + ((start != "") ? "-" : "") + end + "]" + "[" + category + "]";
	}
	return lineAppend;
}