//@author A0116410Y
#include "stdafx.h"
#include "BaseClassLogic.h"

BaseClassLogic::BaseClassLogic(string fileName) try : fileHandler(fileName)
{
}

catch (const exception& ex) 
{
	throw runtime_error(ex.what());
}

BaseClassLogic::BaseClassLogic(vector<string> testVector) : fileHandler(testVector)
{
	isTestMode = true;
}

BaseClassLogic::BaseClassLogic(string fileName, string date, vector<string> keywords, int displayCase) try : fileHandler(fileName)
{
	this->date = date;
	this->keywords = keywords;
	this->displayCase = displayCase;
	updateSortedEntries();
}

catch (const exception& ex)
{
	throw runtime_error(ex.what());
}

BaseClassLogic::BaseClassLogic(vector<string> testVector, string date, vector<string> keywords, int displayCase) : fileHandler(testVector)
{
	this->date = date;
	this->keywords = keywords;
	this->displayCase = displayCase;
	updateSortedEntries();
	isTestMode = true;
}

BaseClassLogic::~BaseClassLogic()
{
}

void BaseClassLogic::toLog(string log)
{
	FileLogic logger("log.txt");
	logger.appendToFile(log);
}

// Start of FileLogic Interface methods
int BaseClassLogic::getEntriesSize()
{
	return fileHandler.getSize();
}

vector<string> BaseClassLogic::getEntriesVector()
{
	return fileHandler.getVector();
}

string BaseClassLogic::getLineFromPositionNumber(int position)
{
	return fileHandler.getLineFromPositionNumber(position);
}

void BaseClassLogic::appendToFile(string lineEntry)
{
	fileHandler.appendToFile(lineEntry);
}

void BaseClassLogic::addToPositionNumber(int position, string lineEntry)
{
	fileHandler.addToPositionNumber(position, lineEntry);
}

void BaseClassLogic::editLine(int position, string newLineEntry)
{
	fileHandler.editLine(position, newLineEntry);
}

void BaseClassLogic::deleteLine(int position) 
{
	fileHandler.deleteLine(position);
}

string BaseClassLogic::createAttributedEntry(string attribute, string entry)
{
	return FileLogic::createAttributedEntry(attribute, entry);
}

string BaseClassLogic::getAttributeEntry(string attribute, string lineEntry)
{
	return FileLogic::getAttributeEntry(attribute, lineEntry);
}

string BaseClassLogic::addAttributedEntryToLineEntry(string attributedEntry, string lineEntry)
{
	return FileLogic::addAttributedEntryToLineEntry(attributedEntry, lineEntry);
}

string BaseClassLogic::deleteAttributedEntryFromLineEntry(string attribute, string lineEntry)
{
	return FileLogic::deleteAttributedEntryFromLineEntry(attribute, lineEntry);
}

string BaseClassLogic::editAttributedEntryFromLineEntry(string attribute, string newAttributeEntry, string lineEntry)
{
	return FileLogic::editAttributedEntryFromLineEntry(attribute, newAttributeEntry, lineEntry);
}
// End of FileLogic Interface methods

// Start of TimeLogic Interface methods
TimeLogic BaseClassLogic::createTimeLogic(string date, string time)
{
	TimeLogic obj(date, time);
	return obj;
}

bool BaseClassLogic::getTimeFormatCheck(TimeLogic obj)
{
	return obj.getTimeFormatCheck();
}

string BaseClassLogic::getStringDate(TimeLogic obj)
{
	return obj.getStringDate();
}

string BaseClassLogic::getStringTime(TimeLogic obj)
{
	return obj.getStringTime();
}

string BaseClassLogic::returnPlusOne(TimeLogic obj)
{
	return obj.returnPlusOne();
}

bool BaseClassLogic::isFirstEarlierThanSecond(TimeLogic time1, TimeLogic time2)
{
	return TimeLogic::isFirstEarlierThanSecond(time1, time2);
}

bool BaseClassLogic::isTimeBeforeNow(TimeLogic time1)
{
	return TimeLogic::isTimeBeforeNow(time1);
}

string BaseClassLogic::getTimeNowInString()
{
	return TimeLogic::getTimeNowInString();
}

TimeLogic BaseClassLogic::addHours(TimeLogic obj, int hours, int min)
{
	obj.addHours(hours, min);
	return obj;
}
// End of TimeLogic Interface methods

vector<string> BaseClassLogic::getSortedLineEntries()
{
	return sortedLineEntries;
}

vector<int> BaseClassLogic::getSortedLinePositions()
{
	return sortedLineFilePositions;
}

void BaseClassLogic::updateSortedEntries()
{
	sortedLineEntries.clear();
	sortedLineFilePositions.clear();
	if (displayCase == 0){
		getListOfEventsHome(date);
	}
	else if (displayCase == -1) {
		getAllEntries();
	}
	else{
		getListOfEventsHaving(keywords);
	}
}

string BaseClassLogic::getDate()
{
	return date;
}

void BaseClassLogic::getListOfEventsHaving(vector<string> keywords)
{
	int size = getEntriesSize();

	for (int i = 0; i < size; ++i) {
		string line = getLineFromPositionNumber(i);
		if (isDateAndTimeCorrect(line)) {
			if (checkKeywordCriteria(line, keywords)) {
				if (getAttributeEntry(TYPE_ATTRIBUTE, line) == FLOAT_TASK_TYPE) {
					sortedLineEntries.push_back(line);
					sortedLineFilePositions.push_back(i);
				}
				else if (!isParameterStringEmpty(getAttributeEntry(TYPE_ATTRIBUTE, line))) {
					addNonFloatEventToEntry(i);
				}
			}
		}
	}
}

void BaseClassLogic::getListOfEventsHome(string fromDate)
{
	int size = fileHandler.getSize();

	TimeLogic dateQualifier = createTimeLogic(date, START_OF_DAY_TIME);

	for (int i = 0; i < size; ++i) {
		string line = getLineFromPositionNumber(i);
		if (isDateAndTimeCorrect(line)) {
			if (getAttributeEntry(TYPE_ATTRIBUTE, line) == FLOAT_TASK_TYPE && getAttributeEntry(COMPLETE_ATTRIBUTE, line) != TASK_COMPLETE) {
				sortedLineEntries.push_back(line);
				sortedLineFilePositions.push_back(i);
			}
			else if (!isParameterStringEmpty(getAttributeEntry(TYPE_ATTRIBUTE, line))) {
				string lineDateString = getAttributeEntry(DATE_ATTRIBUTE, line);
				TimeLogic lineDate = createTimeLogic(lineDateString, START_OF_DAY_TIME);
				if (getAttributeEntry(TYPE_ATTRIBUTE, line) == TIMED_TASK_TYPE){
					string endTime = getAttributeEntry(END_ATTRIBUTE, line);
					lineDate = createTimeLogic(lineDateString, endTime);
				}
				bool isNotCompleted = getAttributeEntry(COMPLETE_ATTRIBUTE, line) == TASK_NOT_COMPLETE;

				if (getTimeFormatCheck(lineDate)) {
					if (isFirstEarlierThanSecond(dateQualifier, lineDate) || isNotCompleted) {
						addNonFloatEventToEntry(i);
					}
				}
			}
		}
	}
}

void BaseClassLogic::getAllEntries()
{
	int size = getEntriesSize();

	for (int i = 0; i < size; ++i) {
		string line = getLineFromPositionNumber(i);
		if (isDateAndTimeCorrect(line)) {
			if (getAttributeEntry(TYPE_ATTRIBUTE, line) == FLOAT_TASK_TYPE) {
				sortedLineEntries.push_back(line);
				sortedLineFilePositions.push_back(i);
			}
			else if (!isParameterStringEmpty(getAttributeEntry(TYPE_ATTRIBUTE, line))) {
				addNonFloatEventToEntry(i);
			}
		}
	}
}

TimeLogic BaseClassLogic::getPriorityDateTime(string line)
{
	string lineDate = getAttributeEntry(DATE_ATTRIBUTE, line);
	string lineTime;
	if (getAttributeEntry(TYPE_ATTRIBUTE, line) == DEADLINE_TASK_TYPE) {
		lineTime = getAttributeEntry(END_ATTRIBUTE, line);
	}
	else if (getAttributeEntry(TYPE_ATTRIBUTE, line) == TIMED_TASK_TYPE) {
		lineTime = getAttributeEntry(START_ATTRIBUTE, line);
	}
	TimeLogic priorityDateTime = createTimeLogic(lineDate, lineTime);
	return priorityDateTime;
}

void BaseClassLogic::addNonFloatEventToEntry(int iteration)
{
	string line = fileHandler.getLineFromPositionNumber(iteration);

	if (sortedLineEntries.size() == 0) {
		sortedLineEntries.push_back(line);
		sortedLineFilePositions.push_back(iteration);
	}
	else {
		vector<string>::iterator it1 = sortedLineEntries.begin();
		vector<int>::iterator it2 = sortedLineFilePositions.begin();
		int minSize = 0;
		int maxSize = sortedLineEntries.size() - 1;

		// Addition of Non-Float Entry is done using binary search to minimise complexity.
		while (maxSize >= minSize) {
			int mid = (minSize + maxSize) / 2;
			string checkLine = sortedLineEntries[mid];

			if (getAttributeEntry(TYPE_ATTRIBUTE, checkLine) == FLOAT_TASK_TYPE) {
				if (maxSize == minSize) {
					sortedLineEntries.insert(it1 + minSize, line);
					sortedLineFilePositions.insert(it2 + minSize, iteration);
					break;
				}
				else {
					maxSize = mid;
				}
			}
			else {
				TimeLogic checkLineTimeLogic = getPriorityDateTime(checkLine);
				TimeLogic deadline = getPriorityDateTime(line);

				bool isEqualDateTime = (checkLineTimeLogic.getStringTime() == deadline.getStringTime()) && (checkLineTimeLogic.getStringDate() == deadline.getStringDate());
				bool isDeadlinePrioritise = (getAttributeEntry(TYPE_ATTRIBUTE, line) == DEADLINE_TASK_TYPE) && (getAttributeEntry(TYPE_ATTRIBUTE, checkLine) == TIMED_TASK_TYPE) && isEqualDateTime;

				if ((isFirstEarlierThanSecond(deadline, checkLineTimeLogic) && !isEqualDateTime) || isDeadlinePrioritise) {
					if (maxSize == minSize) {
						sortedLineEntries.insert(it1 + minSize, line);
						sortedLineFilePositions.insert(it2 + minSize, iteration);
						break;
					}
					else {
						maxSize = mid;
					}
				}
				else {
					if (minSize == maxSize) {
						sortedLineEntries.push_back(line);
						sortedLineFilePositions.push_back(iteration);
						break;
					}
					else {
						minSize = mid + 1;
					}
				}
			}
		}
	}
}

bool BaseClassLogic::checkKeywordCriteria(string line, vector<string> keywords)
{
	bool isCriteriaMet = false;
	int numKeywords = keywords.size();
	for (int i = 0; i < numKeywords && !isCriteriaMet; ++i) {
		string keyword = keywords[i];
		bool isMatchName = getAttributeEntry(NAME_ATTRIBUTE, line) == keyword;
		bool isMatchCategory = getAttributeEntry(CATEGORY_ATTRIBUTE, line) == keyword;

		string lineDate = getAttributeEntry(DATE_ATTRIBUTE, line);
		TimeLogic date = createTimeLogic(lineDate, START_OF_DAY_TIME);

		string lineEnd = getAttributeEntry(END_ATTRIBUTE, line);
		TimeLogic endTime = createTimeLogic(lineDate, lineEnd);

		bool isMatchDate = lineDate == keyword && getTimeFormatCheck(date);
		bool isMatchEndDate = getStringDate(endTime) == keyword && getTimeFormatCheck(endTime);
		
		string lineStart = getAttributeEntry(START_ATTRIBUTE, line);
		TimeLogic startTime = createTimeLogic(lineDate, lineStart);
		bool isMatchStart = lineStart == keyword && getTimeFormatCheck(startTime);
		bool isMatchEnd = getStringTime(endTime) == keyword && getTimeFormatCheck(endTime);

		bool isWithinTime = checkIfTimedTaskWithinTimeKeyword(line, keyword);
		isCriteriaMet = isMatchName || isMatchCategory || isMatchDate || isMatchEndDate || isMatchStart || isMatchEnd || isWithinTime;
	}
	return isCriteriaMet;
}

bool BaseClassLogic::checkIfTimedTaskWithinTimeKeyword(string line, string timeKeyword)
{
	bool isWithinTime = false;
	if (getAttributeEntry(TYPE_ATTRIBUTE, line) == TIMED_TASK_TYPE) {
		string lineDate = getAttributeEntry(DATE_ATTRIBUTE, line);
		string lineStart = getAttributeEntry(START_ATTRIBUTE, line);
		string lineEnd = getAttributeEntry(END_ATTRIBUTE, line);

		TimeLogic startTime = createTimeLogic(lineDate, lineStart);
		TimeLogic endTime = createTimeLogic(lineDate, lineEnd);
		TimeLogic keywordTime = createTimeLogic(lineDate, timeKeyword);

		isWithinTime = isFirstEarlierThanSecond(startTime, keywordTime) && isFirstEarlierThanSecond(keywordTime, endTime);
		if (lineEnd.substr(5, 2) == "+1") {
			TimeLogic keywordTimePlusOne = createTimeLogic(lineDate, timeKeyword + "+1");
			isWithinTime = isFirstEarlierThanSecond(startTime, keywordTimePlusOne) && isFirstEarlierThanSecond(keywordTimePlusOne, endTime);
		}
	}
	return isWithinTime;
}

bool BaseClassLogic::isDateAndTimeCorrect(string lineEntry)
{
	string date = getAttributeEntry(DATE_ATTRIBUTE, lineEntry);
	string startTime = getAttributeEntry(START_ATTRIBUTE, lineEntry);
	string endTime = getAttributeEntry(END_ATTRIBUTE, lineEntry);
	string type = getAttributeEntry(TYPE_ATTRIBUTE, lineEntry);

	bool isDateEmpty = isParameterStringEmpty(getAttributeEntry(DATE_ATTRIBUTE, lineEntry));
	bool isStartTimeEmpty = isParameterStringEmpty(getAttributeEntry(START_ATTRIBUTE, lineEntry));
	bool isEndTimeEmpty = isParameterStringEmpty(getAttributeEntry(END_ATTRIBUTE, lineEntry));

	if (isStartTimeEmpty && isEndTimeEmpty && isDateEmpty && type == FLOAT_TASK_TYPE) {
		return true;
	}
	else if (isStartTimeEmpty && isEndTimeEmpty && type == FLOAT_TASK_TYPE) {
		TimeLogic check = createTimeLogic(date, START_OF_DAY_TIME);
		return getTimeFormatCheck(check);
	}
	else if (isStartTimeEmpty && type == DEADLINE_TASK_TYPE) {
		TimeLogic check = createTimeLogic(date, endTime);
		return getTimeFormatCheck(check);
	}
	else {
		TimeLogic checkStart = createTimeLogic(date, startTime);
		TimeLogic checkEnd = createTimeLogic(date, endTime);

		return (getTimeFormatCheck(checkStart) && getTimeFormatCheck(checkEnd)
			&& isFirstEarlierThanSecond(checkStart, checkEnd) && startTime != endTime);
	}
}

void BaseClassLogic::execute(map<string, string> lineEntries)
{
	assert(false && "THIS SHOULD NOT BE ACCESSED!!!");
}

void BaseClassLogic::execute(map<string, int> fromToPositions)
{
	assert(false && "THIS SHOULD NOT BE ACCESSED!!!");
}

void BaseClassLogic::execute(map<string, int> fromToPositions, int executionCase)
{
	assert(false && "THIS SHOULD NOT BE ACCESSED!!!");
}

void BaseClassLogic::execute(map<string, int> position, map<string, string> lineEntries)
{
	assert(false && "THIS SHOULD NOT BE ACCESSED!!!");
}

vector<vector<string>> BaseClassLogic::displayEvents()
{
	vector<vector<string>> placeHolder;
	assert(false && "THIS SHOULD NOT BE ACCESSED!!!");
	return placeHolder;
}

vector<string> BaseClassLogic::createKeywords(string input)
{
	vector<string> placeHolder;
	assert(false && "THIS SHOULD NOT BE ACCESSED!!!");
	return placeHolder;
}

string BaseClassLogic::formatContentsToLineEdit(int position) 
{
	string placeHolder;
	assert(false && "THIS SHOULD NOT BE ACCESSED!!!");
	return placeHolder;
}

pair <string, string> BaseClassLogic::getEarliestFreeSlot(map<string, string> fromToTime, map<string, int> duration)
{
	pair <string, string> placeHolder;
	assert(false && "THIS SHOULD NOT BE ACCESSED!!!");
	return placeHolder;
}

pair <int, int> BaseClassLogic::getTodayCompletionStat(string todayDate)
{
	pair <int, int> placeHolder;
	assert(false && "THIS SHOULD NOT BE ACCESSED!!!");
	return placeHolder;
}

stack<string> BaseClassLogic::getLinesForUndo()
{
	return OldLineEntriesForUndo;
}

stack<int> BaseClassLogic::getPosForUndo()
{
	return oldLinePosforUndo;
}

bool BaseClassLogic::isParameterStringEmpty(string parameter)
{
	return parameter.find_first_not_of(' ') == std::string::npos;
}