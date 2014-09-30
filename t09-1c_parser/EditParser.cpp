#include "stdafx.h"
#include "EditParser.h"
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

// edit [01/09/2014][2] [event][newInput][date][newInput][time][newInput][category][newInput]
// I assume the codes written are only meant to read user input in blocks of []?

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

string EditParser::extractLeadingBracketContent(string arguments)
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

string EditParser::nextArguments(string argument)
{
	string delimiter = "]";
	argument.erase(0, argument.find(delimiter) + 1);
	return argument;
}

void EditParser::extractDate(string arguments)
{
	string date = extractLeadingBracketContent(arguments);
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

void EditParser::extractTime(string iterArguments)
{
	string time = extractLeadingBracketContent(iterArguments);
	time = ParserHelperFunctions::removeWhiteSpace(time);

	size_t position1 = arguments.find("-");
	if (time.size() == 0) {}
	if (position1 != string::npos  && time.size() == 9) {
		string start = time.substr(0, 4);
		string end = time.substr(5, 4);
		if (ParserHelperFunctions::isParameterStringANumber(start) &&
			ParserHelperFunctions::isParameterStringANumber(end)) {
			start.insert(2, ":");
			end.insert(2, ":");
			parsedData.start = start;
			parsedData.start = end;
		}
		else {
			argumentError();
		}
	}
	else if (position1 == string::npos  && time.size() == 4) {
		if (ParserHelperFunctions::isParameterStringANumber(time)) {
			time.insert(2, ":");
			parsedData.end = time;
		}
		else {
			argumentError();
		}
	}
	else {
		argumentError();
	}

}

string EditParser::extractLine(string iterArguments)
{
	string lineNum = extractLeadingBracketContent(iterArguments);
	string noSpaceLineNum = ParserHelperFunctions::removeWhiteSpace(lineNum);
	if (lineNum.size() == 0) {}
	else if (ParserHelperFunctions::isParameterStringANumber(noSpaceLineNum))
	{
		string extractedNum = noSpaceLineNum;
		return extractedNum;
	}
	else {
		return argumentError();
	}
}

ParsedDataPackage EditParser::parseAndReturn(string parseInput)
{
	extractDate(parseInput);
	parseInput = nextArguments(parseInput);
	parsedData.lineNum = extractLine(parseInput);

	while (extractLeadingBracketContent(parseInput) != "") {
		string parameter = extractLeadingBracketContent(parseInput);
		parseInput = nextArguments(parseInput);

		if (parameter == "event") {
			parsedData.name = extractLeadingBracketContent(parseInput);
		}
		else if (parameter == "date") {
			parsedData.date = extractLeadingBracketContent(parseInput);
		}
		else if (parameter == "time") {
			extractTime(parseInput);
		}
		else if (parameter == "category") {
			parsedData.category = extractLeadingBracketContent(parseInput);
		}
		else {
			argumentError();
		}
	}

	return parsedData;
}