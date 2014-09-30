#pragma once
#ifndef EDIT_PARSER
#define EDIT_PARSER

#include "BaseClassParser.h"
#include "ParsedDataPackage.h"
#include "AddParser.h"
#include "DeleteParser.h"
#include <vector>

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

// Delete Syntax: delete [010914][2]

// Edit Syntax: edit [010914][3] [eventName][date][start-end][category]

using namespace std;

class EditParser :
	public BaseClassParser
{
private:
	string arguments;
	AddParser add;
	DeleteParser del;

public:
	EditParser();
	~EditParser();
	vector<ParsedDataPackage> parseAndReturn(string parseInput);

	void setArguments(string input);
	string argumentError();
};

#endif

