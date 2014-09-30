#include "stdafx.h"
#include "DeleteParser.h"
#include "TimeParser.h"
#include "ParserHelperFunctions.h"

// Syntax: [eventName][date][start-end][category] - timed
// Syntax: [eventName][date][deadline][category] - deadline
// Syntax: [eventName][][][category] - float
// category is to be made optional. 
// ie syntax can just be  [eventName][][][]
// Allowed overloads: event ((next)day of week or date) HHMM / event date HHMM to HHMM
// eg. Watch movie tomorrow / Watch movie next tuesday 1700 / watch movie next tuesday 1300 to 1500
// eg. Watch movie 191014 1700 to 1800
// delete 01/09/2014 1   will search for date variable, which can be used to locate file location with numbered tasks

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
void DeleteParser::setArguments(string input)
{
	arguments = input;
}
string DeleteParser::extractLeadingBracketContent(string arguments)
{
	string contents = "";
	size_t position1 = arguments.find("[");
	size_t position2 = arguments.find("]");

	if (position1 == string::npos || position2 == string::npos) {
		return contents;
	}
	else {
		contents = arguments.substr(position1 + 1, position2 - position1 - 1);
		return contents;
	}
}
string DeleteParser::nextArguments(string argument)
{
	string delimiter = "]";
	argument.erase(0, argument.find(delimiter) + 1);
	return argument;
}

void DeleteParser::extractDate(string iterArguments)
{
	string date = extractLeadingBracketContent(iterArguments);
	string noSpaceDate = ParserHelperFunctions::removeWhiteSpace(date);
	if (date.size() == 0) {}
	else if (ParserHelperFunctions::isParameterStringANumber(noSpaceDate)) {

		if (date.length() == 6) {
			parsedData.date = TimeParser::formatDate(noSpaceDate);
		}
		else {
			argumentError();
		}
	}
	else {
		string newDateFormat = TimeParser::parseDayOfWeek(date);
		if (newDateFormat != date) { //parseDayOfWeek returns unchanged if error
			parsedData.date = date;
		}
		else {
			argumentError();
		}
	}
}
void DeleteParser::extractLine(string iterArguments)
{
	string lineNum = extractLeadingBracketContent(iterArguments);
	string noSpaceLineNum = ParserHelperFunctions::removeWhiteSpace(lineNum);
	if (lineNum.size() == 0) {}
	else if (ParserHelperFunctions::isParameterStringANumber(noSpaceLineNum))
	{
		string extractedNum = noSpaceLineNum;
	}
	else {
		argumentError();
	}
}
ParsedDataPackage DeleteParser::parseAndReturn(string parseInput)
{
	
	extractDate(parseInput);
	parseInput = nextArguments(parseInput);
	parsedData.category = extractLeadingBracketContent(parseInput);

	return parsedData;
}