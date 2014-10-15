#include "stdafx.h"
#include "AddParser.h"
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

AddParser::AddParser() : parsedData()
{
}


AddParser::~AddParser()
{
}

string AddParser::argumentError()
{
	return ADD_PARSER_ERROR;
}

string AddParser::extractLeadingBracketContent(string arguments)
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

string AddParser::nextArguments(string argument)
{
	string delimiter = "]";
	argument.erase(0, argument.find(delimiter) + 1);
	return argument;
}

string AddParser::extractDate(string iterArguments)
{
	string date = extractLeadingBracketContent(iterArguments);
	string noSpaceDate = ParserHelperFunctions::removeWhiteSpace(date);
	if (date.size() == 0) {
		return "";
	}
	else if (ParserHelperFunctions::isParameterStringANumber(noSpaceDate)) {

		if (noSpaceDate.length() == 6) {
			return TimeParser::formatDate(noSpaceDate);
		}
		else {
			setErrorString(ADD_PARSER_6DIGIT_DATE_ERROR);
			setErrorTrue();

			return "";
		}
	}
	else {
		string newDateFormat = TimeParser::parseDayOfWeek(date);
		if (newDateFormat != date) { //parseDayOfWeek returns unchanged if error
			return newDateFormat;
		}
		else {
			setErrorString(ADD_PARSER_DAY_OF_WEEK_ERROR);
			setErrorTrue();

			return "";
		}
	}
}

void AddParser::extractTime(string iterArguments)
{
	string time = extractLeadingBracketContent(iterArguments);
	time = ParserHelperFunctions::removeWhiteSpace(time);

	size_t position1 = time.find("-");
	if (time.size() == 0) {}
	if (position1 != string::npos  && time.size() == 9) {
		string start = time.substr(0, 4);
		string end = time.substr(5, 4);
		if (ParserHelperFunctions::isParameterStringANumber(start) &&
			ParserHelperFunctions::isParameterStringANumber(end)) {
			start.insert(2, ":");
			end.insert(2, ":");
			parsedData.start = start;
			parsedData.end = end;
		}
		else {
			setErrorString(ADD_PARSER_START_END_TIME_ERROR);
			setErrorTrue();
		}
	}
	else if (position1 == string::npos  && time.size() == 4) {
		if (ParserHelperFunctions::isParameterStringANumber(time)) {
			time.insert(2, ":");
			parsedData.end = time;
		}
		else {
			setErrorString(ADD_PARSER_TIME_ERROR);
			setErrorTrue();
		}
	}
	else {
		setErrorString(ADD_PARSER_TIME_ERROR);
		setErrorTrue();
	}
	
}

ParsedDataPackage AddParser::parseAndReturn(string parseInput) 
{
	parsedData.name = extractLeadingBracketContent(parseInput);
	parseInput = nextArguments(parseInput);
	parsedData.date = extractDate(parseInput);
	parseInput = nextArguments(parseInput);
	extractTime(parseInput);
	parseInput = nextArguments(parseInput);
	parsedData.category = extractLeadingBracketContent(parseInput);

	return parsedData;
}

void AddParser::setErrorString(string errorString)
{
	error = errorString;
}

void AddParser::setErrorTrue()
{
	errorPresent = true;
}

bool AddParser::isInputValid()
{
	return errorPresent;
}