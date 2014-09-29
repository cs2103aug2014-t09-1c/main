#pragma once
#ifndef EDIT_PARSER
#define EDIT_PARSER

#include "BaseClassParser.h"
#include "ParsedDataPackage.h"

#include <string>

#define EDIT_PARSER_ERROR \
	"Unable to Commit. Please refer to \"help\" for guide to input."

// Syntax: [eventName][date][start-end][category] - timed
// Syntax: [eventName][date][deadline][category] - deadline
// Syntax: [eventName][][][category] - float
// category is to be made optional. 
// ie syntax can just be  [eventName][][][]
// Allowed overloads: event ((next)day of week or date) HHMM / event date HHMM to HHMM
// eg. Watch movie tomorrow / Watch movie next tuesday 1700 / watch movie next tuesday 1300 to 1500
// eg. Watch movie 191014 1700 to 1800
// delete 01/09/2014 1   will search for date variable, which can be used to locate file location with numbered tasks

// edit [01/09/2014][2] [event][newInput][date][newInput][time][newInput][category][newInput]
// I assume the codes written are only meant to read user input in blocks of []?

using namespace std;

class EditParser :
	public BaseClassParser
{
private:
	string arguments;

public:
	EditParser();
	~EditParser();
	ParsedDataPackage parseAndReturn(string parseInput);

	string argumentError();
	string extractLeadingBracketContent(string arguments);
	string nextArguments(string argument);
	void extractDate(string arguments);
	void extractTime(string iterArguments);
	string extractLine(string iterArguments);
};

#endif

