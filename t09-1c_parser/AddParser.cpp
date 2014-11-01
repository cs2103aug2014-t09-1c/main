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
	if (time.size() == 0) {
		parsedData.start = "";
		parsedData.end = "";
	}
	else if (position1 != string::npos) {
		string start = time.substr(0, 4);
		string end = time.substr(5, time.size() - 1);
		
		bool isValidTimeForOneDay = time.size() == 9 &&
			ParserHelperFunctions::isParameterStringANumber(start) &&
			ParserHelperFunctions::isParameterStringANumber(end);
		bool isValidTimeSpanningTwoDays = time.size() == 11 &&
			ParserHelperFunctions::isParameterStringANumber(start) &&
			ParserHelperFunctions::isParameterStringANumber(end.substr(0, 4)) &&
			end.substr(4, 2) == "+1";

		if (isValidTimeForOneDay || isValidTimeSpanningTwoDays) {
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
	parsedData.name = extractEvent(parseInput);
	parsedData.date = extractDateNL(parseInput);
	extractTimeNL(parseInput);
	parsedData.category = extractCategory(parseInput);

	return parsedData;
}

string AddParser::extractEvent(string arguments)
{
	string event = "";
	string dateCheck = "";
	string keyword = "on ";

	size_t position1 = arguments.rfind(keyword);
	size_t position2 = arguments.find(" ", position1 + 3, 1);

	if (position1 == string::npos || position2 == string::npos || position1 == 0) {
		setErrorString(ADD_PARSER_ERROR);
		setErrorTrue();

		return "";		
	}
	else {
		dateCheck = arguments.substr(position1 + 3, position2 - position1 - 3);

		if ((ParserHelperFunctions::isParameterStringANumber(dateCheck) && dateCheck.size() == 6) || 
			dateCheck == "next" || ParserHelperFunctions::isDayValid(dateCheck)) {
			event = arguments.substr(0, position1 - 1);

			if ((event.find_first_not_of(' ') != string::npos)) {
				return event;
			}
			else {
				setErrorString(ADD_PARSER_NO_EVENT_ERROR);
				setErrorTrue();

				return "";
			}
		}
		else {
			setErrorString(ADD_PARSER_ERROR);
			setErrorTrue();

			return "";
		}
	}
}

string AddParser::extractDateNL(string iterArguments)
{
	string keyword = "on ";

	size_t position1 = iterArguments.rfind(keyword);
	size_t position2 = iterArguments.find(" ", position1 + 3, 1);
	size_t position3 = iterArguments.find(" ", position2 + 1, 1);

	string date = "";
	string dateCheck = iterArguments.substr(position1 + 3, position2 - position1 - 3);
	string day = iterArguments.substr(position2 + 1, position3 - position2 - 1);

	if (parsedData.name.empty()) {
		return "";
	}
	else if (ParserHelperFunctions::isParameterStringANumber(dateCheck) && dateCheck.size() == 6) {

		date = TimeParser::formatDate(iterArguments.substr(position1 + 3, 6));

		return date;
	}
	else if (dateCheck == "next") {
		if (ParserHelperFunctions::isDayValid(day)) {
			date = dateCheck + " " + day;

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
		else {
			setErrorString(ADD_PARSER_DAY_OF_WEEK_ERROR);
			setErrorTrue();

			return "";
		}
	}
	else if (ParserHelperFunctions::isDayValid(dateCheck)) {
		string newDateFormat = TimeParser::parseDayOfWeek(dateCheck);

		if (newDateFormat != dateCheck) { //parseDayOfWeek returns unchanged if error
			return newDateFormat;
		}
		else {
			setErrorString(ADD_PARSER_DAY_OF_WEEK_ERROR);
			setErrorTrue();

			return "";
		}
	}
	else {
		setErrorString(ADD_PARSER_ERROR);
		setErrorTrue();

		return "";
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

		if (ParserHelperFunctions::isParameterStringANumber(endTime) && endTime.size() == 4) {
			endTime.insert(2, ":");
			parsedData.end = endTime;
		}
		else {
			setErrorString(ADD_PARSER_TIME_ERROR);
			setErrorTrue();
		}
	}
	else if (position2 != string::npos && position3 != string::npos) {
		size_t position5 = iterArguments.find(" ", position2 + 5, 1);
		startTime = iterArguments.substr(position2 + 5, position5 - position2 - 5);
	
		size_t position6 = iterArguments.find(" ", position3 + 3, 1);
		endTime = iterArguments.substr(position3 + 3, position6 - position3 - 3);

		bool isValidTimeForOneDay = startTime.size() == 4 && 
			endTime.size() == 4 &&
			ParserHelperFunctions::isParameterStringANumber(startTime) &&
			ParserHelperFunctions::isParameterStringANumber(endTime);
		bool isValidTimeSpanningTwoDays = startTime.size() == 4 && 
			endTime.size() == 6 &&
			ParserHelperFunctions::isParameterStringANumber(startTime) &&
			ParserHelperFunctions::isParameterStringANumber(endTime.substr(0, 4)) &&
			endTime.substr(4, 2) == "+1";

		if (isValidTimeForOneDay || isValidTimeSpanningTwoDays) {
			startTime.insert(2, ":");
			endTime.insert(2, ":");
			parsedData.start = startTime;
			parsedData.end = endTime;
		}
		else {
			setErrorString(ADD_PARSER_START_END_TIME_ERROR);
			setErrorTrue();
		}
	}
	else {
		setErrorString(ADD_PARSER_TIME_ERROR);
		setErrorTrue();
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

string AddParser::getErrorString()
{
	return error;
}