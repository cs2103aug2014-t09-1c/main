#pragma once
#ifndef SEARCH_PARSER
#define SEARCH_PARSER

#define SEARCH_PARSER_ERROR \
	"Unable to Commit. Please refer to \"help\" for guide to input."
#define SEARCH_PARSER_NO_DATE_ERROR \
	"Please enter a date!"
#define SEARCH_PARSER_6DIGIT_DATE_ERROR \
	"Please enter a valid DDMMYY date!"
#define SEARCH_PARSER_DAY_OF_WEEK_ERROR \
	"Please enter a valid day of the week!"
#define SEARCH_PARSER_NO_TYPE_ERROR \
	"Please enter a type of \"name\", \"date\" or \"category!\""


#include "BaseClassParser.h"
#include "ParsedDataPackage.h"
#include <string>

using namespace std;

// Syntax: [eventName]<start><end><rating><@category> - timed
// Syntax: [eventName]<deadline><rating><@category> - deadline
// Syntax: [eventName]<rating><@category> - float
// Allowed overloads: event ((next)day of week or date) HHMM / event date HHMM to HHMM
// eg. Watch movie tomorrow / Watch movie next tuesday 1700 / watch movie next tuesday 1300 to 1500
// eg. Watch movie 191014 1700 to 1800

class SearchParser :
	public BaseClassParser
{
private:
	string extractLeadingBracketContent(string arguments);
	string nextArguments(string arguments);
	string extractDate(string arguments);
	void extractTime(string arguments);
	void checkTimeisRange(string input);
	void checkDurationisValid(string input);
	void getDuration(string input);

public:
	SearchParser();
	
	~SearchParser();
	string parseSearchArgs(string parseInput);
	ParsedDataPackage parsefreeSlotCheck(string parseInput);

};

#endif