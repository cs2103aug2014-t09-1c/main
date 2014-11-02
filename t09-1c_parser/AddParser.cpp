#include "stdafx.h"
#include "AddParser.h"
#include "TimeParser.h"
#include "ParserHelperFunctions.h"

// Syntax: [eventName][date][start-end][category] - timed
// Syntax: [eventName][date][deadline][category] - deadline
// Syntax: [eventName][][][category] - float
// category is to be made optional. 
// ie syntax can just be  [eventName][][][]

// Natural Language Syntax: meeting with boss on 191014 from 1700 to 1800 @boss - timed
// Natural Language Syntax: meeting with boss on 191014 from 1700 to 1800+1 @boss - timed with next day
// Natural Language Syntax: meeting with boss on 101014 at 1700 @boss - deadline
// category is made optional in NL
// **NOT IMPLEMENTED** Natural Language Syntax: meeting with boss @boss - float
// **NOT IMPLEMENTED** Natural Language Syntax: meeting with boss - float without category 

// Allowed overloads: event ((next)day of week or date) HHMM / event date HHMM to HHMM
// eg. Watch movie tomorrow / Watch movie next tuesday 1700 / watch movie next tuesday 1300 to 1500
// eg. Watch movie 191014 1700 to 1800

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

ParsedDataPackage AddParser::parseNLandReturn(string parseInput)
{
	try {
		parsedData.name = extractEvent(parseInput);
		parsedData.date = extractDateNL(parseInput);
		extractTimeNL(parseInput);
		parsedData.category = extractCategory(parseInput);
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
	string keyword = "on ";

	size_t position1 = arguments.rfind(keyword);
	size_t position2 = arguments.find(" ", position1 + 3, 1);

	if (position1 == string::npos || position2 == string::npos || position1 == 0) {
		throw runtime_error(ADD_PARSER_ERROR);
	}
	else {
		dateCheck = arguments.substr(position1 + 3, position2 - position1 - 3);

		if (ParserHelperFunctions::isParameterStringANumber(dateCheck) && dateCheck.size() == 6) {
			event = arguments.substr(0, position1 - 1);

			if ((event.find_first_not_of(' ') != string::npos)) {
				return event;
			}
			else {
				throw runtime_error(ADD_PARSER_NO_EVENT_ERROR);
			}
		}
		else {
			throw runtime_error(ADD_PARSER_ERROR);
		}
	}
}

string AddParser::extractDateNL(string iterArguments)
{
	string date = "";

	if (parsedData.name.empty()) {
		return "";
	}
	else {
		string keyword = "on ";
		size_t position1 = iterArguments.rfind(keyword);

		date = formatDate(iterArguments.substr(position1 + 3, 6));

		return date;
	}
}

void AddParser::extractTimeNL(string iterArguments)
{
	string startTime = "";
	string endTime = "";
	string keyword1 = "at ";
	string keyword2 = "from ";
	string keyword3 = "to ";
	size_t position1 = iterArguments.rfind(keyword1);
	size_t position2 = iterArguments.rfind(keyword2);
	size_t position3 = iterArguments.rfind(keyword3);

	if (parsedData.name == "" && parsedData.date == "") {
		parsedData.start = "";
		parsedData.end = "";
	}
	else if (position1 != string::npos) {
		size_t position4 = iterArguments.find(" ", position1 + 3, 1);
		endTime = iterArguments.substr(position1 + 3, position4 - position1 - 3);

		if (isParameterStringANumber(endTime) && endTime.size() == 4) {
			endTime.insert(2, ":");
			parsedData.end = endTime;
		}
		else {
			throw runtime_error(ADD_PARSER_TIME_ERROR);
		}
	}
	else if (position2 != string::npos && position3 != string::npos) {
		size_t position5 = iterArguments.find(" ", position2 + 5, 1);
		startTime = iterArguments.substr(position2 + 5, position5 - position2 - 5);

		size_t position6 = iterArguments.find(" ", position3 + 3, 1);
		endTime = iterArguments.substr(position3 + 3, position6 - position3 - 3);

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

	if (parsedData.name == "") {
		return "";
	}
	else if (position1 != string::npos) {
		category = arguments.substr(position1 + 1);
		return category;
	}
	else {
		return category;
	}
}