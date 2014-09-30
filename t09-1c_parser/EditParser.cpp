#include "stdafx.h"
#include "EditParser.h"
#include "TimeParser.h"
#include "ParserHelperFunctions.h"
#include <string>

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

EditParser::EditParser()
{
}


EditParser::~EditParser()
{
}

string EditParser::argumentError()
{
	return EDIT_PARSER_ERROR;
}

void EditParser::setArguments(string input)
{
	arguments = input;
}

vector<ParsedDataPackage> EditParser::parseAndReturn(string parseInput)
{
	vector<ParsedDataPackage> parsedDatas;

	string deleteArguments = parseInput.substr(0, 11);
	string addArguments = parseInput.substr(13, parseInput.length() - 12);

	parsedDatas.assign(1, del.parseAndReturn(deleteArguments));
	parsedDatas.assign(1, add.parseAndReturn(addArguments));

	return parsedDatas;
}