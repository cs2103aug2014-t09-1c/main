#pragma once
#ifndef DELETE_PARSER
#define DELETE_PARSER

#include "BaseClassParser.h"
#include "ParsedDataPackage.h"
#include "AddParser.h"
#include <string>

#define DELETE_PARSER_ERROR \
	"Unable to Commit. Please refer to \"help\" for guide to input."
#define DELETE_PARSER_LINE_NUM_ERROR \
	"Please enter the line number of the task you wish to delete!"

using namespace std;

// Syntax: [eventName][date][start-end][category] - timed
// Syntax: [eventName][date][deadline][category] - deadline
// Syntax: [eventName][][][category] - float
// category is to be made optional. 
// ie syntax can just be  [eventName][][][]
// Allowed overloads: event ((next)day of week or date) HHMM / event date HHMM to HHMM
// eg. Watch movie tomorrow / Watch movie next tuesday 1700 / watch movie next tuesday 1300 to 1500
// eg. Watch movie 191014 1700 to 1800

// Delete Syntax: delete [010914][2] or delete [3]

class DeleteParser :
	public BaseClassParser
{
private:
	AddParser add;

public:
	string excessInput;

	DeleteParser();
	~DeleteParser();
	ParsedDataPackage parseAndReturn(string parseInput);

	string argumentError();

	void extractLine(string iterArguments);

	void setErrorString(string errorString);
	void setErrorTrue();
	bool isInputValid();
	
};

#endif