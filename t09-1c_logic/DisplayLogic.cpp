#include "stdafx.h"
#include "DisplayLogic.h"

DisplayLogic::DisplayLogic(string fileName, string date, vector<string> keywords, int displayCase) try : BaseClassLogic(fileName, date, keywords, displayCase)
{
}

catch (const exception& ex)
{
	throw runtime_error(ex.what());
}

DisplayLogic::DisplayLogic(vector<string> testVector, string date, vector<string> keywords, int displayCase) : BaseClassLogic(testVector, date, keywords, displayCase)
{
}

DisplayLogic::~DisplayLogic()
{
}

vector<string> DisplayLogic::putToVectorEventDatails(string line)
{
	vector<string> eventVector;
	eventVector.push_back(getAttributeEntry(NAME_ATTRIBUTE, line));
	eventVector.push_back(getAttributeEntry(CATEGORY_ATTRIBUTE, line));
	
	string pos2;
	if (getAttributeEntry(START_ATTRIBUTE, line) != "") {
		if (getAttributeEntry(DATE_ATTRIBUTE, line) == getDate()) {
			pos2 = TODAY + getAttributeEntry(START_ATTRIBUTE, line);
		}
		else {
			pos2 = getAttributeEntry(DATE_ATTRIBUTE, line) + " " + getAttributeEntry(START_ATTRIBUTE, line);
		}
	}
	else {
		pos2 = NO_START_STRING;
	}

	string pos3;
	TimeLogic endDate = createTimeLogic(getAttributeEntry(DATE_ATTRIBUTE, line), getAttributeEntry(END_ATTRIBUTE, line));

	if (getStringTime(endDate) != "") {
		if (getStringDate(endDate) == getDate()) {
			pos3 = TODAY + getStringTime(endDate);
		}
		else {
			pos3 = getStringDate(endDate) + " " + endDate.getStringTime();
		}
	}
	else {
		pos2 = FLOAT_START_STRING;
		pos3 = FLOAT_END_STRING;
	}
	eventVector.push_back(pos2);
	eventVector.push_back(pos3);
	bool isNotComplete = getAttributeEntry(COMPLETE_ATTRIBUTE, line) == "no";
	string displayComplete = (isTimeBeforeNow(endDate) && isNotComplete) ? LAPSED : getAttributeEntry(COMPLETE_ATTRIBUTE, line);
	eventVector.push_back(displayComplete);

	return eventVector;
}

vector<vector<string>> DisplayLogic::displayEvents()
{
	vector<vector<string>> toDisplay;
	vector<string> eventList = getSortedLineEntries();
	for (size_t i = 0; i < eventList.size(); ++i) {
		vector<string> parsedEvent = putToVectorEventDatails(eventList[i]);
		toDisplay.push_back(parsedEvent);
	}
	return toDisplay;
}

string DisplayLogic::formatContentsToLineEdit(int position)
{
	string lineAppend;
	vector<string> eventList = getSortedLineEntries();
	int size = eventList.size();
	if (position <= size) {
		string line = eventList[position - 1];
		string name = getAttributeEntry(NAME_ATTRIBUTE, line);
		string date = getAttributeEntry(DATE_ATTRIBUTE, line);
		if (date.length() == 10) {
			date = date.substr(0, 2) + date.substr(3, 2) + date.substr(8, 2);
		}
		string start = getAttributeEntry(START_ATTRIBUTE, line);
		if (start.length() == 5) {
			start = start.substr(0, 2) + start.substr(3, 2);
		}
		string end = getAttributeEntry(END_ATTRIBUTE, line);
		if (end.length() == 5) {
			end = end.substr(0, 2) + end.substr(3, 2);
		}
		else if (end.length() == 7) {
			end = end.substr(0, 2) + end.substr(3, 4);
		}
		string category = getAttributeEntry(CATEGORY_ATTRIBUTE, line);

		lineAppend = "[" + name + "]" + "[" + date + "]" + "[" + start + ((start != "") ? "-" : "") + end + "]" + "[" + category + "]";
	}
	return lineAppend;
}

