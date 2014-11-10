//@author A0116410Y
#pragma once
#ifndef BASE_CLASS_LOGIC
#define BASE_CLASS_LOGIC

#include "FileLogic.h"
#include "TimeLogic.h"
#include <stack>
#include <map>
#include "assert.h"

#define CREATION_ATTRIBUTE \
	"CreationDate"
#define NAME_ATTRIBUTE \
	"name"
#define DATE_ATTRIBUTE \
	"date"
#define START_ATTRIBUTE \
	"start"
#define END_ATTRIBUTE \
	"end"
#define CATEGORY_ATTRIBUTE \
	"category"
#define COMPLETE_ATTRIBUTE \
	"complete"
#define TYPE_ATTRIBUTE \
	"type"
#define FROM_POSITION \
	"fromPos"
#define TO_POSITION \
	"toPos"

#define DEADLINE_TASK_TYPE \
	"deadline"
#define TIMED_TASK_TYPE \
	"timed"
#define FLOAT_TASK_TYPE \
	"float"
#define TASK_NOT_COMPLETE \
	"no"
#define TASK_COMPLETE \
	"yes"
#define START_OF_DAY_TIME \
	"00:00"
#define END_OF_DAY_TIME \
	"23:59"


class BaseClassLogic
{
private:
	FileLogic fileHandler;
	string date;
	vector<string> keywords;
	int displayCase;

	/*These are the private sorting methods applicable to all Logic specific methods.
	These sorting methods provide the algorithm that will provide the fixed
	sort of to-dos for the user interface, which is different from the sort
	in the file. */	
	void getListOfEventsHome(string fromDate);

	/*These are the private sorting helper methods applicable to all Logic specific methods.*/
	TimeLogic getPriorityDateTime(string line);
	void addNonFloatEventToEntry(int iteration);
	bool checkKeywordCriteria(string line, vector<string> keywords);
	bool checkIfTimedTaskWithinTimeKeyword(string line, string timeKeyword);

	/*These are the private sorting helper variables applicable to all Logic specific methods.*/
	vector<string> sortedLineEntries; //This stores the sorted entries as determined by the sorting algorithm
	vector<int> sortedLineFilePositions; // This stores the filePositions of each entry in lineEntries respectively.

protected:
	BaseClassLogic(string fileName);
	BaseClassLogic(string fileName, string date, vector<string> keywords, int displayCase);
	BaseClassLogic(vector<string> testVector);
	BaseClassLogic(vector<string> testVector, string date, vector<string> keywords, int displayCase);
	virtual ~BaseClassLogic();

	bool isTestMode = false;
	void toLog(string log);

	/*These are the interface methods for the FileLogic class.
	  Consult FileLogic.h for more information about these methods. */
	string getLineFromPositionNumber(int position);
	void appendToFile(string lineEntry);
	void addToPositionNumber(int position, string lineEntry);
	void editLine(int position, string newLineEntry);
	void deleteLine(int position);
	string createAttributedEntry(string attribute, string entry);
	string getAttributeEntry(string attribute, string lineEntry);
	string addAttributedEntryToLineEntry(string attributedEntry, string lineEntry);
	string deleteAttributedEntryFromLineEntry(string attribute, string lineEntry);
	string editAttributedEntryFromLineEntry(string attribute, string newAttributeEntry, string lineEntry);

	/*These are the interface methods for the TimeLogic class.
	  Consult TimeLogic.h for more information about these methods. */
	TimeLogic createTimeLogic(string date, string time);
	bool getTimeFormatCheck(TimeLogic obj);
	string getStringDate(TimeLogic obj);
	string getStringTime(TimeLogic obj);
	string returnPlusOne(TimeLogic obj);
	bool isFirstEarlierThanSecond(TimeLogic time1, TimeLogic time2);
	bool isTimeBeforeNow(TimeLogic time1);
	string getTimeNowInString();
	TimeLogic addHours(TimeLogic obj, int hours, int min);

	/*These are the protected sorting methods applicable to all Logic specific methods.
	  These sorting methods provide the algorithm that will provide the fixed
	  sort of to-dos for the user interface, which is different from the sort
	  in the file. */
	void getListOfEventsHaving(vector<string> keywords);
	void getAllEntries();
	void updateSortedEntries();

	/* These methods are protected helper functions applicable to all Logic specific methods.*/
	bool isParameterStringEmpty(string parameter);
	bool isDateAndTimeCorrect(string lineEntry);
	string getDate();

	stack<string> OldLineEntriesForUndo;
	stack<int> oldLinePosforUndo;

public:
	/*These are the public interface methods for the FileLogic class.
	  These methods are the only necessary methods for automated testing purposes.
	  Consult FileLogic.h or this file for more information about these methods. */
	int getEntriesSize();
	vector<string> getEntriesVector();
	vector<string> getSortedLineEntries();
	vector<int> getSortedLinePositions();

	/*These are the virtual methods for BaseClassLogic child classes. These should not
	be accessed without the use of the child class's method. Should that occur,
	assertion failure will occur.*/
	virtual void execute(map<string,string> lineEntries);
	virtual void execute(map<string, int> fromToPositions);
	virtual void execute(map<string, int> fromToPositions, int executionCase);
	virtual void execute(map<string, int> position, map<string, string> lineEntries);
	virtual vector<vector<string>> displayEvents();

	virtual vector<string> createKeywords(string input);
	virtual string formatContentsToLineEdit(int position);
	virtual pair <string, string> getEarliestFreeSlot(map<string, string> fromToTime, map<string, int> duration);
	virtual pair <int, int> getTodayCompletionStat(string todayDate);

	/*These methods is to access the old line entries and positions that have been
	modified for Undo Logic storage and later retrieval*/
	stack<string> getLinesForUndo();
	stack<int> getPosForUndo();
};

#endif