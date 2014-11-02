#include "stdafx.h"
#include "SearchLogic.h"
#include "DL_Algorithm.h"


SearchLogic::SearchLogic(string fileName) try : BaseClassLogic(fileName)
{
}

catch (const exception& ex)
{
	throw runtime_error(ex.what());
}

SearchLogic::SearchLogic(vector<string> testVector) : BaseClassLogic(testVector)
{
}

SearchLogic::~SearchLogic()
{
}
		
vector<string> SearchLogic::createKeywords(string input)
{
	DL_Algorithm diffCost;
	transform(input.begin(), input.end(), input.begin(), ::tolower);

	if (input.length() >= MIMUMUM_LENGTH) {
		int numberOfEvents = getEntriesSize();
		for (int i = 0; i < numberOfEvents; ++i) {
			string line = getLineFromPositionNumber(i);
			string lineCategory = getAttributeEntry(CATEGORY_ATTRIBUTE, line);
			int categoryDifference = diffCost.findDLCost(input, lineCategory);
			if (categoryDifference <= NONDATETIMEMAXCOST) {
				string categoryChars = lineCategory;
				transform(categoryChars.begin(), categoryChars.end(), categoryChars.begin(), ::tolower);
				categoryDifference = (categoryChars.find(input) != string::npos) ? -1 : categoryDifference;
				determinePriority(lineCategory, categoryDifference);
			}

			string lineName = getAttributeEntry(NAME_ATTRIBUTE, line);
			int nameDifference = diffCost.findDLCost(input, lineName);
			if (nameDifference <= NONDATETIMEMAXCOST) {
				string nameChars = lineName;
				transform(nameChars.begin(), nameChars.end(), nameChars.begin(), ::tolower);
				nameDifference = (nameChars.find(input) != string::npos) ? -1 : nameDifference;
				determinePriority(lineName, nameDifference);
			}

			string lineDate = getAttributeEntry(DATE_ATTRIBUTE, line);
			string lineEnd = getAttributeEntry(END_ATTRIBUTE, line);
			TimeLogic endDateTime = createTimeLogic(lineDate, lineEnd);
			string endDate = getStringDate(endDateTime);
			
			int lineDateDifference = diffCost.findDLCost(input, lineDate);
			int endDateDifference = diffCost.findDLCost(input, endDate);

			if (lineDateDifference <= DATETIMEMAXCOST || endDateDifference <= DATETIMEMAXCOST) {
				TimeLogic dateCheck = createTimeLogic(lineDate, "00:00");
				if (getTimeFormatCheck(dateCheck) && getTimeFormatCheck(dateCheck)) {
					determinePriority(lineDate, lineDateDifference);
					determinePriority(endDate, endDateDifference);
				}
			}
			string endTime = getStringTime(endDateTime);
			int endDifference = diffCost.findDLCost(input, endTime);

			if (endDifference <= DATETIMEMAXCOST)
			{
				if (endDateTime.getTimeFormatCheck()) {
					determinePriority(endTime, endDifference);
				}
			}

			if (getAttributeEntry(TYPE_ATTRIBUTE, line) == "timed") {
				if (checkTimedTaskEligibility(input, line)) {
					determinePriority(input, 0);
				}
			}
		}
		
	}
	return keywords;
}

void SearchLogic::determinePriority(string keyword, int diffCost) 
{
	int size = keywords.size();

	bool isCopy = false;
	for (int i = 0; i < size; ++i) {
		string suggestion = keywords[i];
		if (keyword == suggestion) {
			isCopy = true;
			break;
		}
	}

	if (!isCopy) {
		if (keywords.size() == 0) {
			keywords.push_back(keyword);
			keywordPriority.push_back(diffCost);
		}
		else {
			for (int i = 0; i < size; ++i) {
				if (keywordPriority[i] >= diffCost) {
					vector<string>::iterator it1;
					it1 = keywords.begin() + i;
					keywords.insert(it1, keyword);

					vector<int>::iterator it2;
					it2 = keywordPriority.begin() + i;
					keywordPriority.insert(it2, diffCost);

					if (keywords.size() > SUGGESTIONS_LIMIT) {
						keywords.resize(SUGGESTIONS_LIMIT);
					}
					break;
				}
			}
		}
	}
}

bool SearchLogic::checkTimedTaskEligibility(string input, string line)
{
	bool isEligible;

	string date = getAttributeEntry(DATE_ATTRIBUTE, line);
	string start = getAttributeEntry(START_ATTRIBUTE, line);
	string end = getAttributeEntry(END_ATTRIBUTE, line);

	TimeLogic startTime = createTimeLogic(date, start);
	TimeLogic endTime = createTimeLogic(date, end);
	TimeLogic inputTime = createTimeLogic(date, input);

	isEligible = isFirstEarlierThanSecond(startTime, inputTime) && isFirstEarlierThanSecond(inputTime, endTime);
	if (!isEligible && end.substr(5, 2) == "+1") {
		TimeLogic inputTimePlusOne = createTimeLogic(date, input + "+1");
		isEligible = isFirstEarlierThanSecond(startTime, inputTimePlusOne) && isFirstEarlierThanSecond(inputTimePlusOne, endTime);
	}
	return isEligible;
}

pair<string, string> SearchLogic::getEarliestFreeSlot(map<string, string> fromToTime, map<string, int> duration)
{
	string date = fromToTime[DATE_ATTRIBUTE];
	string fromTime = fromToTime[START_ATTRIBUTE];
	string toTime = fromToTime[END_ATTRIBUTE];
	int hoursToAdd = duration[FROM_POSITION];
	int minsToAdd = duration[TO_POSITION];

	string start;
	string end;
	if (hoursToAdd <= 23 && minsToAdd <= 59) {
		string iterDate = date;
		string iterTime = fromTime;
		TimeLogic to(date, toTime);

		vector<string> dateKey;
		dateKey.push_back(date);
		getListOfEventsHaving(dateKey);
		vector<string> eventList = getSortedLineEntries();
		int size = eventList.size();
		for (int i = 0; i < size; ++i) {
			string line = eventList[i];
			if (getAttributeEntry(TYPE_ATTRIBUTE, line) == "timed") {
				string lineDate = getAttributeEntry(DATE_ATTRIBUTE, line);
				string lineStart = getAttributeEntry(START_ATTRIBUTE, line);
				string lineEnd = getAttributeEntry(END_ATTRIBUTE, line);
				TimeLogic lineStartTime = createTimeLogic(lineDate, lineStart);
				TimeLogic lineEndTime = createTimeLogic(lineDate, lineEnd);
				TimeLogic addedTime = createTimeLogic(iterDate, iterTime);
				bool isLineEndingEarlier = isFirstEarlierThanSecond(lineEndTime, addedTime);
				addedTime = addHours(addedTime, hoursToAdd, minsToAdd);
				if ((isFirstEarlierThanSecond(addedTime, to) && isFirstEarlierThanSecond(addedTime, lineStartTime))) {
					break;
				}
				else if (!isLineEndingEarlier) {
					iterDate = getStringDate(lineEndTime);
					iterTime = getStringTime(lineEndTime);
				}
			}
		}
		TimeLogic addedTime = createTimeLogic(iterDate, iterTime);
		addedTime = addHours(addedTime, hoursToAdd, minsToAdd);
		if (isFirstEarlierThanSecond(addedTime, to)) {
			date = iterDate;
			start = iterTime;
			end = getStringTime(addedTime) + returnPlusOne(addedTime);
		}
	}
	string uiDate, uiTime;
	if (!start.empty() && !end.empty()) {
		uiDate = date.substr(0, 2) + date.substr(3, 2) + date.substr(8, 2);
		uiTime = start.substr(0, 2) + start.substr(3, 2) + "-" + end.substr(0, 2) + end.substr(3, end.size()-3);
	}
	pair<string, string> pairTime(uiDate, uiTime);
	return pairTime;
}

pair<int, int> SearchLogic::getTodayCompletionStat(string todayDate)
{
	vector<string> dateKey;
	dateKey.push_back(todayDate);
	getListOfEventsHaving(dateKey);
	vector<string> eventList = getSortedLineEntries();
	int completed = 0;
	int eventsToday = eventList.size();
	for (int i = 0; i < eventsToday; ++i) {
		if (getAttributeEntry(COMPLETE_ATTRIBUTE, eventList[i]) == "yes") {
			++completed;
		}
	}
	pair<int, int> stats(completed, eventsToday);
	return stats;
}