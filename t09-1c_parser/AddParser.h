#pragma once
#ifndef ADD_PARSER
#define ADD_PARSER

#include "BaseClassParser.h"

// Syntax: [eventName][date][start-end][category] - timed
// Syntax: [eventName][date][deadline][category] - deadline
// Syntax: [eventName][][][category] - float
// category is to be made optional. 
// ie syntax can just be  [eventName][][][]

// Allowed overloads: event ((next)day of week or date) HHMM / event date HHMM to HHMM
// eg. Watch movie on tomorrow / Watch movie on next tuesday at 1700 / watch movie on next tuesday from 1300 to 1500
// eg. Watch movie on 1910140 from 1700 to 1800

// Natural Language: Date overload [OK], time (eg. 1800+1) [OK]
// 
// NL Category:
// Parsed first and removed from arguments to cater for float events.
//
// NL Event:
// Parsed in a way depended on keyword " on " from NL Date.
// Without " on ", automatically parsed as float event. With " on ", checks for valid Date format.
//
// NL Date:
// Must be after keyword " on ". (eg. Watch movie on tomorrow at 1700.)
// Invalid format after keyword " on " will be treated as a float event. (eg. Sitting on the roof top)
// 
// NL Time:
// Must be after keyword(s) " at " for deadline, (" from ", " to ") for timed.
// Invalid format after keyword(s) will return error.


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
	ParsedDataPackage parseNLAndReturn(string parseInput);

	// Natural Language Parsing
	string extractCategoryNL(string arguments);
	string removeCategoryNL(string arguments);
	string extractEventNL(string arguments);
	string extractDateNL(string arguments);
	void extractTimesNL(string arguments);
	void syntaxSwapChecker(string arguments);

};

#endif
