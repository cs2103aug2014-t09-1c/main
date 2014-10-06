#include "stdafx.h"
#include "DeleteParser.h"
#include "ParserHelperFunctions.h"

// Syntax: [eventName][date][start-end][category] - timed
// Syntax: [eventName][date][deadline][category] - deadline
// Syntax: [eventName][][][category] - float
// category is to be made optional. 
// ie syntax can just be  [eventName][][][]
// Allowed overloads: event ((next)day of week or date) HHMM / event date HHMM to HHMM
// eg. Watch movie tomorrow / Watch movie next tuesday 1700 / watch movie next tuesday 1300 to 1500
// eg. Watch movie 191014 1700 to 1800

// Delete Syntax: delete [010914][2]

DeleteParser::DeleteParser()
{
}


DeleteParser::~DeleteParser()
{
}

string DeleteParser::argumentError()
{
	return DELETE_PARSER_ERROR;
}


void DeleteParser::extractLine(string iterArguments)
{
	string lineNum = add.extractLeadingBracketContent(iterArguments);

	if (ParserHelperFunctions::isParameterStringANumber(lineNum)){
		parsedData.lineNum = stoi(lineNum);
	}
	else {
		argumentError();
	}
}

ParsedDataPackage DeleteParser::parseAndReturn(string parseInput)
{
	parsedData.date = add.extractDate(parseInput);
	parseInput = add.nextArguments(parseInput);
	extractLine(parseInput);
	
	excessInput = add.nextArguments(parseInput);

	return parsedData;
}