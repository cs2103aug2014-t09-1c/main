#include "stdafx.h"
#include "AddParser.h"
#include "TimeParser.h"
#include "ParserHelperFunctions.h"

// Syntax: [eventName][date][start-end][category] - timed
// Syntax: [eventName][date][deadline][category] - deadline
// Syntax: [eventName][][][category] - float
// category is to be made optional. 
// ie syntax can just be  [eventName][][][]

// Natural Language Syntax: meeting with boss on 191014 at 1700 "boss"

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

ParsedDataPackage AddParser::parseNLandReturn(string parseInput)
{
	string arguments = parseInput;
	string event = "";
	string dateKeyword = "on";
	string timeKeyword = "at";
	string timeKeyword2 = "from";
	string categoryKeyword = "\"";

	bool isDateExtracted = false;
	bool isTimeExtracted = false;
	bool isCategoryExtracted = false;


	// Parse Category
	size_t found = arguments.rfind(categoryKeyword);
	size_t found2 = arguments.rfind(categoryKeyword, found);

	if (found != string::npos && found2 != string::npos) {
		string category = arguments.substr(found2, found - found2 + 1);
		parsedData.category = category;
		isCategoryExtracted = true;
		arguments.resize(arguments.size() - found2);
	}
	else if (found2 == string::npos) { // Only one " is found
		setErrorString(ADD_PARSER_CATEGORY_ERROR);
		setErrorTrue();
	}
	else {
		parsedData.category = "";
	}


	// Parse Time
	size_t found3 = arguments.rfind(timeKeyword);

	if (found3 != string::npos) {
		string checkTime = arguments.substr(found3 + 3, 4);

		if (ParserHelperFunctions::isParameterStringANumber(checkTime)) {
			size_t found4 = arguments.find(" ", found3 + 3, 1); // find position of space behind time
			string time = arguments.substr(found3 + 3, found4 - found3 + 3); // extract any time string, 1700 or 1700-1900
			extractTime(time);
			isTimeExtracted = true;
			arguments.resize(arguments.size() - found3);
		}
	}
	
	size_t found5 = arguments.rfind(timeKeyword2);

	if (found5 != string::npos) {
		if (isTimeExtracted = false) {
			string checkTime2 = arguments.substr(found5 + 3, 4);

			if (ParserHelperFunctions::isParameterStringANumber(checkTime2)) {
				size_t found6 = arguments.find(" ", found5 + 3, 1); // find position of space behind time
				string time = arguments.substr(found5 + 3, found6 - found5 + 3); // extract any time string, 1700 or 1700-1900
				extractTime(time);
				isTimeExtracted = true;
				arguments.resize(arguments.size() - found5);
			}
		}	
	}

	if (isTimeExtracted = false) {
		parsedData.start = "";
		parsedData.end = "";
	}
	

	// Parse Date
	size_t found7 = arguments.rfind(dateKeyword); // find last occurence of "on" which most probably be related to date
	string checkDate = arguments.substr(found7 + 3, 6); // check format of string behind keyword "on"

	if (ParserHelperFunctions::isParameterStringANumber(checkDate)) {
		parsedData.date = extractDate(checkDate);
		isDateExtracted = true;
		arguments.resize(arguments.size() - found7);
	}
	else {
		parsedData.date = "";
	}
	

	// Parse Event
	parsedData.name = arguments;


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