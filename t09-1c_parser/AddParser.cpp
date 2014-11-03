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
// eg. Watch movie on tomorrow / Watch movie on next tuesday at 1700 / watch movie on next tuesday from 1300 to 1500
// eg. Watch movie on 1910140 from 1700 to 1800

// Natural Language: Date overload [OK], time (eg. 1800+1) [OK]
// 
// NL Category:
// Parsed first and removed from arguments to cater for float events.
//
// NL Event:
// Parsed in a way depended on keyword " on " from NL Date.
// Without " on ", automatically parsed as float event. With " on ", checks for valid Date format.
//
// NL Date:
// Must be after keyword " on ". (eg. Watch movie on tomorrow at 1700.)
// Invalid format after keyword " on " will be treated as a float event. (eg. Sitting on the roof top)
// 
// NL Time:
// Must be after keyword(s) " at " for deadline, (" from ", " to ") for timed.
// Invalid format after keyword(s) will return error.


AddParser::AddParser() : BaseClassParser()
{
}

AddParser::~AddParser()
{
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
	try{
		string date = extractLeadingBracketContent(iterArguments);
		string resultDate = getDate(date);
		return resultDate;
	}
	catch (const exception& ex){
		throw runtime_error(ex.what());
	}
}

void AddParser::extractTime(string iterArguments)
{
	try {
		string time = extractLeadingBracketContent(iterArguments);
		getAndStoreTimes(time);
	}
	catch (const exception& ex){
		throw runtime_error(ex.what());
	}
}

ParsedDataPackage AddParser::parseAndReturn(string parseInput)
{
	try {
		insertAttribute(NAME_ATTRIBUTE, extractLeadingBracketContent(parseInput));
		parseInput = nextArguments(parseInput);
		insertAttribute(DATE_ATTRIBUTE, extractDate(parseInput));
		parseInput = nextArguments(parseInput);
		extractTime(parseInput);
		parseInput = nextArguments(parseInput);
		insertAttribute(CATEGORY_ATTRIBUTE, extractLeadingBracketContent(parseInput));
		return parsedData;
	}
	catch (const exception& ex){
		throw runtime_error(ex.what());
	}
}

ParsedDataPackage AddParser::parseNLAndReturn(string parseInput)
{
	try {
		parsedData.category = extractCategory(parseInput);
		parseInput = removeCategory(parseInput);
		parsedData.name = extractEvent(parseInput);
		parsedData.date = extractDateNL(parseInput);
		extractTimeNL(parseInput);
		return parsedData;
	}
	catch (const exception& ex){
		throw runtime_error(ex.what());
	}
}

string AddParser::extractEvent(string arguments)
{
	string event = "";
	string dateCheck = "";
	string keyword = " on ";

	size_t position1 = arguments.rfind(keyword);
	size_t position2 = arguments.find(" ", position1 + 4, 1);

	if (position1 != string::npos && position2 != string::npos && position1 != 0) {
		dateCheck = arguments.substr(position1 + 4, position2 - position1 - 4);

		if ((ParserHelperFunctions::isParameterStringANumber(dateCheck) && dateCheck.size() == 6) ||
			ParserHelperFunctions::isDateParameterValid(dateCheck)) {
			event = arguments.substr(0, position1);

			if ((event.find_first_not_of(' ') != string::npos)) {
				return event;
			}
			else {
				throw runtime_error(ADD_PARSER_NO_EVENT_ERROR);
			}
		}
		else {
			event = arguments;

			return event;
		}
	}
	else {
		event = arguments;

		return event;
	}
}

string AddParser::extractDateNL(string iterArguments)
{
	string keyword = " on ";

	size_t position1 = iterArguments.rfind(keyword);
	size_t position2 = iterArguments.find(" ", position1 + 4, 1);
	size_t position3 = iterArguments.find(" ", position2 + 1, 1);

	string date = "";
	string dateCheck = iterArguments.substr(position1 + 4, position2 - position1 - 4);
	string day = iterArguments.substr(position2 + 1, position3 - position2 - 1);

	if (parsedData.name.empty()) {
		throw runtime_error(ADD_PARSER_NO_EVENT_ERROR);
	}
	else if (parsedData.name == iterArguments) {
		return "";
	}
	else if (ParserHelperFunctions::isParameterStringANumber(dateCheck) && dateCheck.size() == 6) {

		date = TimeParser::formatDate(iterArguments.substr(position1 + 4, 6));

		return date;
	}
	else if (dateCheck == "next") {
		date = dateCheck + " " + day;

		string newDateFormat = TimeParser::parseDayOfWeek(date);
		if (newDateFormat != date) { //parseDayOfWeek returns unchanged if error
			return newDateFormat;
		}
		else {
			throw runtime_error(ADD_PARSER_DAY_OF_WEEK_ERROR);
		}
	}
	else {
		string newDateFormat = TimeParser::parseDayOfWeek(dateCheck);

		if (newDateFormat != dateCheck) { //parseDayOfWeek returns unchanged if error
			return newDateFormat;
		}
		else {
			throw runtime_error(ADD_PARSER_DAY_OF_WEEK_ERROR);
		}
	}
}

void AddParser::extractTimeNL(string iterArguments)
{
	string startTime = "";
	string endTime = "";
	string keyword1 = " at ";
	string keyword2 = " from ";
	string keyword3 = " to ";
	size_t position1 = iterArguments.rfind(keyword1);
	size_t position2 = iterArguments.rfind(keyword2);
	size_t position3 = iterArguments.rfind(keyword3);

	if (parsedData.name == "" && parsedData.date == "") {
		parsedData.start = "";
		parsedData.end = "";
	}
	else if (parsedData.name == iterArguments) {
		parsedData.start = "";
		parsedData.end = "";
	}
	else if (position1 != string::npos) {
		size_t position4 = iterArguments.find(" ", position1 + 4, 1);
		endTime = iterArguments.substr(position1 + 4, position4 - position1 - 4);

		if (isParameterStringANumber(endTime) && endTime.size() == 4) {
			endTime.insert(2, ":");
			parsedData.end = endTime;
		}
		else {
			throw runtime_error(ADD_PARSER_TIME_ERROR);
		}
	}
	else if (position2 != string::npos && position3 != string::npos) {
		size_t position5 = iterArguments.find(" ", position2 + 6, 1);
		startTime = iterArguments.substr(position2 + 6, position5 - position2 - 6);

		size_t position6 = iterArguments.find(" ", position3 + 4, 1);
		endTime = iterArguments.substr(position3 + 4, position6 - position3 - 4);

		bool isValidTimeForOneDay = startTime.size() == 4 &&
			endTime.size() == 4 &&
			isParameterStringANumber(startTime) &&
			isParameterStringANumber(endTime);
		bool isValidTimeSpanningTwoDays = startTime.size() == 4 &&
			endTime.size() == 6 &&
			isParameterStringANumber(startTime) &&
			isParameterStringANumber(endTime.substr(0, 4)) &&
			endTime.substr(4, 2) == "+1";

		if (isValidTimeForOneDay || isValidTimeSpanningTwoDays) {
			startTime.insert(2, ":");
			endTime.insert(2, ":");
			parsedData.start = startTime;
			parsedData.end = endTime;
		}
		else {
			throw runtime_error(ADD_PARSER_START_END_TIME_ERROR);
		}
	}
	else {
		throw runtime_error(ADD_PARSER_TIME_ERROR);
	}
}

string AddParser::extractCategory(string arguments)
{
	string category = "";
	string keyword = "@";
	size_t position1 = arguments.rfind(keyword);

	if (position1 != string::npos) {
		category = arguments.substr(position1 + 1);
		return category;
	}
	else {
		return category;
	}
}

string AddParser::removeCategory(string arguments)
{
	string keyword = "@";
	size_t position1 = arguments.rfind(keyword);

	if (position1 != string::npos) {
		string newArguments = arguments.substr(0, position1 - 1);

		return newArguments;
	}
	else {
		return arguments;
	}
}