//@author A0111718M
#pragma once
#ifndef BASE_CLASS_PARSER
#define BASE_CLASS_PARSER

#include "ParsedDataPackage.h"
#include "TimeParser.h"

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
#define DELIMETER_START \
	"["
#define DELIMETER_END \
	"]"
#define EMPTY_SPACE_CHAR \
	" "
#define EMPTY_STRING \
	""
#define TIME_INSERT_COLON \
	":"
#define TIME_KEYWORD_AT \
	" at "
#define TIME_KEYWORD_FROM \
	" from "
#define TIME_KEYWORD_TO \
	" to "
#define TIME_KEYWORD_DASH \
	"-"
#define TIME_KEYWORD_SECOND_DAY \
	"+1"
#define DATE_KEYWORD_NEXT \
	"next"
#define DATE_KEYWORD_ON \
	" on "
#define CATEGORY_KEYWORD \
	"@"
#define COMPLETE_PARSE_KEYWORD_TO \
	"to"
#define DELETE_PARSE_KEYWORD_TO \
	"to"
#define PARSER_6DIGIT_DATE_ERROR \
	"Please enter a valid DDMMYY date!"
#define PARSER_DAY_OF_WEEK_ERROR \
	"Please enter a valid date or day of the week!"
#define PARSER_START_END_TIME_ERROR \
	"Please enter a valid HHMM-HHMM start-end time format!"
#define PARSER_TIME_ERROR \
	"Please enter a valid time format!"
#define PARSER_NO_EVENT_ERROR \
	"Please enter a valid event name."
#define PARSER_DAY_OF_WEEK_ERROR \
	"Please enter a valid date or day of the week!"
#define PARSER_SYNTAX_ERROR \
	"Please follow the correct syntax for QuickAdd!"


class BaseClassParser
{
protected:
	ParsedDataPackage parsedData;
	BaseClassParser();
	~BaseClassParser();

	string toLowerCaseString(string input);
	int findMatchingStringIndex(string str, vector<string> lst);
	bool isParameterStringEmpty(string parameter);
	bool isParameterStringANumber(string parameter);
	string removeWhiteSpace(string parameter);

	/*
	* Original date is returned if there is a format error.
	*/
	string parseDayOfWeek(string date);

	/*
	* Return date in DD/MM/YYYY format
	*/
	string formatDate(string date);

	/*
	* Get and store times in HH:MM format. If no time is detected, it will store an empty string.
	*/
	void getAndStoreTimes(string timeString);

	/*
	* Original date is returned if there is a format error.
	*/
	string getDate(string dateString);

	void insertAttribute(string attribute, string entry);
	void insertAttribute(string attribute, int entry);

	bool isDateParameterValid(string day);
	bool isStringNext(string keyword);
	string getEventNL(string arguments);
	string getDateNL(string arguments);

	/*
	* Get and store times in HH:MM format. If no time is detected, it will store an empty string.
	*/
	void getAndStoreTimesNL(string arguments);

	/*
	* Throws an exception if keywords for Natural Language Parsing is not inputted in proper format.
	*/
	void checkForSyntaxSwap(string arguments);

	/*
	* This variable checks if Natural Language Parser detects a float input.
	*/
	int eventSize;

public:
	virtual ParsedDataPackage parseAndReturn(string parseInput);
	virtual ParsedDataPackage parseNLAndReturn(string parseInput);
	virtual string parseSearchArgs(string parseInput);
	virtual int convertToPosition(string argument);
	virtual ParsedDataPackage parsefreeSlotCheck(string input);

};
#endif
