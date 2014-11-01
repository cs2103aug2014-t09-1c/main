#pragma once
#ifndef ADD_PARSER
#define ADD_PARSER

#include "BaseClassParser.h"
#include "ParsedDataPackage.h"

#define ADD_PARSER_ERROR \
	"Unable to Commit. Please enter the correct format."
#define ADD_PARSER_NO_EVENT_ERROR \
	"Please enter a valid event name."
#define ADD_PARSER_6DIGIT_DATE_ERROR \
	"Please enter a valid DDMMYY date!"
#define ADD_PARSER_DAY_OF_WEEK_ERROR \
	"Please enter a valid day of the week!"
#define ADD_PARSER_START_END_TIME_ERROR \
	"Please enter a valid HHMM-HHMM start-end time format!"
#define ADD_PARSER_TIME_ERROR \
	"Please enter a valid time format!"

// Syntax: [eventName][date][start-end][category] - timed
// Syntax: [eventName][date][deadline][category] - deadline
// Syntax: [eventName][][][category] - float
// category is to be made optional. 
// ie syntax can just be  [eventName][][][]

// Natural Language Syntax: meeting with boss on 191014 from 1700 to 1800 @boss - timed
// Natural Language Syntax: meeting with boss on 191014 from 1700 to 1800+1 @boss - timed with next day
// Natural Language Syntax: meeting with boss on 101014 at 1700 @boss - deadline
// category is made optional in NL
// **NOT IMPLEMENTED** Natural Language Syntax: meeting with boss @boss - float
// **NOT IMPLEMENTED** Natural Language Syntax: meeting with boss - float without category 

// Allowed overloads: event ((next)day of week or date) HHMM / event date HHMM to HHMM
// eg. Watch movie tomorrow / Watch movie next tuesday 1700 / watch movie next tuesday 1300 to 1500
// eg. Watch movie 191014 1700 to 1800

class AddParser :
	public BaseClassParser
{
private:
	string extractLeadingBracketContent(string arguments);
	string nextArguments(string arguments);
	string extractDate(string arguments);
	void extractTime(string arguments);

public:
	AddParser();
	~AddParser();
	ParsedDataPackage parseAndReturn(string parseInput);
	ParsedDataPackage parseNLandReturn(string parseInput); // parse Natural Language and Return

	// Natural Language Parsing
	string extractEvent(string arguments);
	string extractDateNL(string arguments);
	void extractTimeNL(string arguments);
	string extractCategory(string arguments);

};

#endif

