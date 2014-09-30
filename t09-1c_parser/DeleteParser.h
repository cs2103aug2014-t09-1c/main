#pragma once
#ifndef DELETE_PARSER
#define DELETE_PARSER

#include "BaseClassParser.h"
#include "ParsedDataPackage.h"

#include <string>

#define DELETE_PARSER_ERROR \
	"Unable to Commit. Please refer to \"help\" for guide to input."
// Syntax: [eventName][date][start-end][category] - timed
// Syntax: [eventName][date][deadline][category] - deadline
// Syntax: [eventName][][][category] - float
// category is to be made optional. 
// ie syntax can just be  [eventName][][][]
// Allowed overloads: event ((next)day of week or date) HHMM / event date HHMM to HHMM
// eg. Watch movie tomorrow / Watch movie next tuesday 1700 / watch movie next tuesday 1300 to 1500
// eg. Watch movie 191014 1700 to 1800


using namespace std;

class DeleteParser :
	public BaseClassParser
{
private:
	string arguments;

public:
	DeleteParser();
	~DeleteParser();
	ParsedDataPackage parseAndReturn(string parseInput);
	string argumentError();
	void setArguments(string arguments);
	string extractLeadingBracketContent(string arguments);
	string nextArguments(string argument);
	void extractDate(string arguments);
	void extractLine(string iterArguments);
	
};

#endif