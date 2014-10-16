#pragma once
#ifndef ADD_PARSER
#define ADD_PARSER

#include "BaseClassParser.h"
#include "ParsedDataPackage.h"
#include <string>

#define ADD_PARSER_ERROR \
	"Unable to Commit. Please refer to \"help\" for guide to input."
#define ADD_PARSER_6DIGIT_DATE_ERROR \
	"Please enter a valid DDMMYY date!"
#define ADD_PARSER_DAY_OF_WEEK_ERROR \
	"Please enter a valid day of the week!"
#define ADD_PARSER_START_END_TIME_ERROR \
	"Please enter a valid HHMM-HHMM start-end time format!"
#define ADD_PARSER_TIME_ERROR \
	"Please enter a valid time format!"

using namespace std;

// Syntax: [eventName]<start><end><rating><@category> - timed
// Syntax: [eventName]<deadline><rating><@category> - deadline
// Syntax: [eventName]<rating><@category> - float
// Allowed overloads: event ((next)day of week or date) HHMM / event date HHMM to HHMM
// eg. Watch movie tomorrow / Watch movie next tuesday 1700 / watch movie next tuesday 1300 to 1500
// eg. Watch movie 191014 1700 to 1800

class AddParser :
	public BaseClassParser
{
private:
	ParsedDataPackage parsedData;

public:
	AddParser();
	~AddParser();
	ParsedDataPackage parseAndReturn(string parseInput);

	string argumentError();

	string extractLeadingBracketContent(string arguments);
	string nextArguments(string arguments);
	string extractDate(string arguments);
	void extractTime(string arguments);

	void setErrorString(string errorString);
	void setErrorTrue();
	bool isInputValid();
	
};

#endif

