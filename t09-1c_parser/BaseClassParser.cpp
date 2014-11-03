#include "stdafx.h"
#include "BaseClassParser.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>


BaseClassParser::BaseClassParser() : parsedData()
{
}


BaseClassParser::~BaseClassParser()
{
}

ParsedDataPackage BaseClassParser::parseAndReturn(string parseInput)
{
	assert(false && "GO AWAY! YOU ShOULN'T BE SEEING THIS");
	return parsedData;
}

ParsedDataPackage BaseClassParser::parseNLAndReturn(string parseInput)
{
	assert(false && "GO AWAY! YOU ShOULN'T BE SEEING THIS");
	return parsedData;
}

string BaseClassParser::parseSearchArgs(string parseInput)
{
	assert(false && "GO AWAY! YOU ShOULN'T BE SEEING THIS");
	return "";
}

void BaseClassParser::insertAttribute(string attribute, string entry)
{
	parsedData.insertAttribute(attribute, entry);
}

void BaseClassParser::insertAttribute(string attribute, int entry)
{
	parsedData.insertAttribute(attribute, entry);
}

string BaseClassParser::toLowerCaseString(string input)
{
	transform(input.begin(), input.end(), input.begin(), ::tolower);
	return input;
}

int BaseClassParser::findMatchingStringIndex(string str, vector<string> lst)
{
	int index = -1;
	int lstSize = lst.size();
	for (int i = 0; i < lstSize; ++i) {
		if (lst[i] == str) {
			index = i;
			break;
		}
	}
	return index;
}

bool BaseClassParser::isParameterStringEmpty(string parameter)
{
	return parameter.find_first_not_of(' ') == std::string::npos;
}

bool BaseClassParser::isParameterStringANumber(string parameter)
{
	if (isParameterStringEmpty(parameter)) {
		return false;
	}
	else {
		return parameter.find_first_not_of("0123456789") == std::string::npos;
	}
}

string BaseClassParser::removeWhiteSpace(string parameter)
{
	parameter.erase(remove(parameter.begin(), parameter.end(), ' '), parameter.end());
	return parameter;
}

string BaseClassParser::parseDayOfWeek(string date)
{
	return TimeParser::parseDayOfWeek(date);
}

string BaseClassParser::formatDate(string date)
{
	return TimeParser::formatDate(date);
}

void BaseClassParser::getAndStoreTimes(string timeString)
{
	string time = timeString;
	time = removeWhiteSpace(time);

	size_t position1 = time.find("-");
	if (time.size() == 0) {
		insertAttribute(START_ATTRIBUTE, "");
		insertAttribute(END_ATTRIBUTE, "");
	}
	else if (position1 != string::npos) {
		string start = time.substr(0, 4);
		string end = time.substr(5, time.size() - 1);

		bool isValidTimeForOneDay = time.size() == 9 && isParameterStringANumber(start) &&
			isParameterStringANumber(end);
		bool isValidTimeSpanningTwoDays = time.size() == 11 &&
			isParameterStringANumber(start) &&
			isParameterStringANumber(end.substr(0, 4)) &&
			end.substr(4, 2) == "+1";

		if (isValidTimeForOneDay || isValidTimeSpanningTwoDays) {
			start.insert(2, ":");
			end.insert(2, ":");
			insertAttribute(START_ATTRIBUTE, start);
			insertAttribute(END_ATTRIBUTE, end);
		}
		else {
			throw runtime_error(PARSER_START_END_TIME_ERROR);
		}
	}
	else if (position1 == string::npos  && time.size() == 4) {
		if (isParameterStringANumber(time)) {
			time.insert(2, ":");
			insertAttribute(START_ATTRIBUTE, "");
			insertAttribute(END_ATTRIBUTE, time);
		}
		else {
			throw runtime_error(PARSER_TIME_ERROR);
		}
	}
	else {
		throw runtime_error(PARSER_TIME_ERROR);
	}
}

string BaseClassParser::getDate(string dateString)
{
	string date = dateString;
	string noSpaceDate = removeWhiteSpace(date);
	if (date.size() == 0) {
		return "";
	}
	else if (isParameterStringANumber(noSpaceDate)) {

		if (noSpaceDate.length() == 6) {
			return formatDate(noSpaceDate);
		}
		else {
			throw runtime_error(PARSER_6DIGIT_DATE_ERROR);
		}
	}
	else {
		string newDateFormat = TimeParser::parseDayOfWeek(date);
		if (newDateFormat != date) { //parseDayOfWeek returns unchanged if error
			return newDateFormat;
		}
		else {
			throw runtime_error(PARSER_DAY_OF_WEEK_ERROR);
		}
	}
}

bool BaseClassParser::isDateParameterValid(string day)
{
	unordered_set<string> set = { "mon", "tues", "wed", "thurs", "fri", "sat", "sun",
		"monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday",
		"today", "tomorrow", "next" };

	unordered_set<string>::const_iterator got = set.find(day);

	if (got == set.end()) {
		return false;
	}
	else {
		return true;
	}
}

string BaseClassParser::getEventNL(string arguments)
{
	string event = "";
	string dateCheck = "";
	string keyword = " on ";

	size_t position1 = arguments.rfind(keyword);
	size_t position2 = arguments.find(" ", position1 + 4, 1);

	if (position1 != string::npos && position2 != string::npos && position1 != 0) {
		dateCheck = arguments.substr(position1 + 4, position2 - position1 - 4);

		if ((isParameterStringANumber(dateCheck) && dateCheck.size() == 6) ||
			isDateParameterValid(dateCheck)) {
			event = arguments.substr(0, position1);

			if ((event.find_first_not_of(' ') != string::npos)) {
				return event;
			}
			else {
				throw runtime_error(PARSER_NO_EVENT_ERROR);
			}
		}
		else {
			event = arguments;
			eventSize = arguments.size();

			return event;
		}
	}
	else if (arguments.find_first_not_of(' ') == string::npos) {
		throw runtime_error(PARSER_NO_EVENT_ERROR);
	}
	else {
		event = arguments;
		eventSize = arguments.size();

		return event;
	}
}

string BaseClassParser::getDateNL(string arguments)
{
	string keyword = " on ";

	size_t position1 = arguments.rfind(keyword);
	size_t position2 = arguments.find(" ", position1 + 4, 1);
	size_t position3 = arguments.find(" ", position2 + 1, 1);

	string date = "";
	string dateCheck = arguments.substr(position1 + 4, position2 - position1 - 4);
	string day = arguments.substr(position2 + 1, position3 - position2 - 1);

	if (arguments.size() == eventSize) {
		return "";
	}
	else if (isParameterStringANumber(dateCheck) && dateCheck.size() == 6) {

		date = formatDate(arguments.substr(position1 + 4, 6));

		return date;
	}
	else if (dateCheck == "next") {
		date = dateCheck + " " + day;

		string newDateFormat = parseDayOfWeek(date);
		if (newDateFormat != date) { //parseDayOfWeek returns unchanged if error
			return newDateFormat;
		}
		else {
			throw runtime_error(PARSER_DAY_OF_WEEK_ERROR);
		}
	}
	else {
		string newDateFormat = parseDayOfWeek(dateCheck);

		if (newDateFormat != dateCheck) { //parseDayOfWeek returns unchanged if error
			return newDateFormat;
		}
		else {
			throw runtime_error(PARSER_DAY_OF_WEEK_ERROR);
		}
	}
}

void BaseClassParser::getAndStoreTimesNL(string arguments)
{
	string startTime = "";
	string endTime = "";
	string keyword1 = " at ";
	string keyword2 = " from ";
	string keyword3 = " to ";
	size_t position1 = arguments.rfind(keyword1);
	size_t position2 = arguments.rfind(keyword2);
	size_t position3 = arguments.rfind(keyword3);

	if (arguments.size() == eventSize) {
		insertAttribute(START_ATTRIBUTE, "");
		insertAttribute(END_ATTRIBUTE, "");
	}
	else if (position1 != string::npos) {
		size_t position4 = arguments.find(" ", position1 + 4, 1);
		endTime = arguments.substr(position1 + 4, position4 - position1 - 4);

		if (isParameterStringANumber(endTime) && endTime.size() == 4) {
			endTime.insert(2, ":");
			insertAttribute(END_ATTRIBUTE, endTime);
		}
		else {
			throw runtime_error(PARSER_TIME_ERROR);
		}
	}
	else if (position2 != string::npos && position3 != string::npos) {
		size_t position5 = arguments.find(" ", position2 + 6, 1);
		startTime = arguments.substr(position2 + 6, position5 - position2 - 6);

		size_t position6 = arguments.find(" ", position3 + 4, 1);
		endTime = arguments.substr(position3 + 4, position6 - position3 - 4);

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
			insertAttribute(START_ATTRIBUTE, startTime);
			insertAttribute(END_ATTRIBUTE, endTime);
		}
		else {
			throw runtime_error(PARSER_START_END_TIME_ERROR);
		}
	}
	else {
		throw runtime_error(PARSER_TIME_ERROR);
	}
}

void BaseClassParser::checkForSyntaxSwap(string arguments)
{
	string keyword1 = " on ";
	string keyword2 = " at ";
	string keyword3 = " from ";
	string keyword4 = "@";

	size_t position1 = arguments.rfind(keyword1);
	size_t position2 = arguments.rfind(keyword2);
	size_t position3 = arguments.rfind(keyword3);
	size_t position4 = arguments.rfind(keyword4);

	if ((position1 > position2) || (position1 > position3) || position4 == 0) {
		throw runtime_error(PARSER_SYNTAX_ERROR);
	}
}