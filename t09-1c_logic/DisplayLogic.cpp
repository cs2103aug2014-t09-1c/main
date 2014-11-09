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

	bool isNotComplete = getAttributeEntry(COMPLETE_ATTRIBUTE, line) == TASK_NOT_COMPLETE;
	string displayComplete = (isTimeBeforeNow(endDate) && isNotComplete) ? LAPSED : getAttributeEntry(COMPLETE_ATTRIBUTE, line);
	displayComplete = (displayComplete == TASK_COMPLETE || displayComplete == TASK_NOT_COMPLETE || displayComplete == LAPSED) ? displayComplete : UNKNOWN;
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
	const int DDMMYYYY_FULL_LENGTH = 10;
	const int HHMM_FULL_LENGTH = 5;
	const int HHMMPLUS1_FULL_LENGTH = 7;
	const int TIME_DATE_COMP_INPUT_SIZE = 2;
	const int PLUS_ONE_SIZE = 2;
	const int MM_POS = 3;


	string lineAppend;
	vector<string> eventList = getSortedLineEntries();
	int size = eventList.size();
	if (position <= size && position > 0) {
		string line = eventList[position - 1];
		string name = getAttributeEntry(NAME_ATTRIBUTE, line);
		string date = getAttributeEntry(DATE_ATTRIBUTE, line);
		if (date.length() == DDMMYYYY_FULL_LENGTH) {
			date = date.substr(0, TIME_DATE_COMP_INPUT_SIZE) + date.substr(MM_POS, TIME_DATE_COMP_INPUT_SIZE) + date.substr(8, TIME_DATE_COMP_INPUT_SIZE);
		}
		string start = getAttributeEntry(START_ATTRIBUTE, line);
		if (start.length() == HHMM_FULL_LENGTH) {
			start = start.substr(0, TIME_DATE_COMP_INPUT_SIZE) + start.substr(MM_POS, TIME_DATE_COMP_INPUT_SIZE);
		}
		string end = getAttributeEntry(END_ATTRIBUTE, line);
		if (end.length() == HHMM_FULL_LENGTH) {
			end = end.substr(0, TIME_DATE_COMP_INPUT_SIZE) + end.substr(MM_POS, TIME_DATE_COMP_INPUT_SIZE);
		}
		else if (end.length() == HHMMPLUS1_FULL_LENGTH) {
			end = end.substr(0, TIME_DATE_COMP_INPUT_SIZE) + end.substr(MM_POS, TIME_DATE_COMP_INPUT_SIZE + PLUS_ONE_SIZE);
		}
		string category = getAttributeEntry(CATEGORY_ATTRIBUTE, line);

		lineAppend = STRUCT_PARAM_FORMAT(name, date, start + ((start != "") ? TIME_DELIMETER : "") + end, category);
	}
	return lineAppend;
}

