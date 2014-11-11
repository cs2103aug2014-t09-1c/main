//@author A0111718M
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

int BaseClassParser::convertToPosition(string argument)
{
	assert(false && "GO AWAY! YOU ShOULN'T BE SEEING THIS");
	return 0;
}

ParsedDataPackage BaseClassParser::parsefreeSlotCheck(string input)
{
	assert(false && "GO AWAY! YOU ShOULN'T BE SEEING THIS");
	return parsedData;
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

	size_t position1 = time.find(TIME_KEYWORD_DASH);

	if (time.size() == 0) {
		insertAttribute(START_ATTRIBUTE, EMPTY_STRING);
		insertAttribute(END_ATTRIBUTE, EMPTY_STRING);
	}
	else if (position1 != string::npos) {
		string start = time.substr(0, 4);
		string end = time.substr(5, time.size() - 1);

		bool isValidTimeForOneDay = time.size() == 9 && isParameterStringANumber(start) &&
			isParameterStringANumber(end);
		bool isValidTimeSpanningTwoDays = time.size() == 11 &&
			isParameterStringANumber(start) &&
			isParameterStringANumber(end.substr(0, 4)) &&
			end.substr(4, 2) == TIME_KEYWORD_SECOND_DAY;

		if (isValidTimeForOneDay || isValidTimeSpanningTwoDays) {
			start.insert(2, TIME_INSERT_COLON);
			end.insert(2, TIME_INSERT_COLON);
			insertAttribute(START_ATTRIBUTE, start);
			insertAttribute(END_ATTRIBUTE, end);
		}
		else {
			throw runtime_error(PARSER_START_END_TIME_ERROR);
		}
	}
	else if (position1 == string::npos  && time.size() == 4) {

		if (isParameterStringANumber(time)) {
			time.insert(2, TIME_INSERT_COLON);
			insertAttribute(START_ATTRIBUTE, EMPTY_STRING);
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
		return EMPTY_STRING;
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

	string lowerCaseDay = toLowerCaseString(day);

	unordered_set<string>::const_iterator got = set.find(lowerCaseDay);

	if (got == set.end()) {
		return false;
	}
	else {
		return true;
	}
}

bool BaseClassParser::isStringNext(string keyword)
{
	string lowerCaseKeyword = toLowerCaseString(keyword);

	if (lowerCaseKeyword == DATE_KEYWORD_NEXT) {
		return true;
	}
	else {
		return false;
	}
}

string BaseClassParser::getEventNL(string arguments)
{
	string event = EMPTY_STRING;
	string dateCheck = EMPTY_STRING;
	string keyword = DATE_KEYWORD_ON;

	size_t position1 = arguments.rfind(keyword);
	size_t position2 = arguments.find(EMPTY_SPACE_CHAR, position1 + 4, 1);

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
	else if (position1 != string::npos && position2 == string::npos) {
		dateCheck = arguments.substr(position1 + 4);

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
	else {
		event = arguments;
		eventSize = arguments.size();

		return event;
	}
}

string BaseClassParser::getDateNL(string arguments)
{
	string keyword = DATE_KEYWORD_ON;

	size_t position1 = arguments.rfind(keyword);
	size_t position2 = arguments.find(EMPTY_SPACE_CHAR, position1 + 4, 1);
	size_t position3 = arguments.find(EMPTY_SPACE_CHAR, position2 + 1, 1);

	string date = EMPTY_STRING;
	string dateCheck = arguments.substr(position1 + 4, position2 - position1 - 4);
	string day = arguments.substr(position2 + 1, position3 - position2 - 1);

	if (arguments.size() == eventSize) {
		return EMPTY_STRING;
	}
	else if (isParameterStringANumber(dateCheck) && dateCheck.size() == 6) {
		date = formatDate(arguments.substr(position1 + 4, 6));

		return date;
	}
	else if (isStringNext(dateCheck)) {
		date = dateCheck + EMPTY_SPACE_CHAR + day;
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
	string startTime = EMPTY_STRING;
	string endTime = EMPTY_STRING;
	string keyword1 = TIME_KEYWORD_AT;
	string keyword2 = TIME_KEYWORD_FROM;
	string keyword3 = TIME_KEYWORD_TO;
	size_t position1 = arguments.rfind(keyword1);
	size_t position2 = arguments.rfind(keyword2);
	size_t position3 = arguments.rfind(keyword3);

	if (arguments.size() == eventSize) {
		insertAttribute(START_ATTRIBUTE, EMPTY_STRING);
		insertAttribute(END_ATTRIBUTE, EMPTY_STRING);
	}
	else if (position1 != string::npos) {
		size_t position4 = arguments.find(EMPTY_SPACE_CHAR, position1 + 4, 1);
		endTime = arguments.substr(position1 + 4, position4 - position1 - 4);

		if (isParameterStringANumber(endTime) && endTime.size() == 4) {
			endTime.insert(2, TIME_INSERT_COLON);
			insertAttribute(END_ATTRIBUTE, endTime);
		}
		else {
			insertAttribute(END_ATTRIBUTE, EMPTY_STRING);
		}
	}
	else if (position2 != string::npos && position3 != string::npos) {
		size_t position5 = arguments.find(EMPTY_SPACE_CHAR, position2 + 6, 1);
		startTime = arguments.substr(position2 + 6, position5 - position2 - 6);

		size_t position6 = arguments.find(EMPTY_SPACE_CHAR, position3 + 4, 1);
		endTime = arguments.substr(position3 + 4, position6 - position3 - 4);

		bool isValidTimeForOneDay = startTime.size() == 4 &&
			endTime.size() == 4 &&
			isParameterStringANumber(startTime) &&
			isParameterStringANumber(endTime);
		bool isValidTimeSpanningTwoDays = startTime.size() == 4 &&
			endTime.size() == 6 &&
			isParameterStringANumber(startTime) &&
			isParameterStringANumber(endTime.substr(0, 4)) &&
			endTime.substr(4, 2) == TIME_KEYWORD_SECOND_DAY;

		if (isValidTimeForOneDay || isValidTimeSpanningTwoDays) {
			startTime.insert(2, TIME_INSERT_COLON);
			endTime.insert(2, TIME_INSERT_COLON);
			insertAttribute(START_ATTRIBUTE, startTime);
			insertAttribute(END_ATTRIBUTE, endTime);
		}
		else {
			throw runtime_error(PARSER_START_END_TIME_ERROR);
		}
	}
	else {
		insertAttribute(START_ATTRIBUTE, EMPTY_STRING);
		insertAttribute(END_ATTRIBUTE, EMPTY_STRING);
	}
}

void BaseClassParser::checkForSyntaxSwap(string arguments)
{
	string keyword1 = DATE_KEYWORD_ON;
	string keyword2 = TIME_KEYWORD_AT;
	string keyword3 = TIME_KEYWORD_FROM;
	string keyword4 = CATEGORY_KEYWORD;

	size_t position1 = arguments.rfind(keyword1);
	size_t position2 = arguments.rfind(keyword2);
	size_t position3 = arguments.rfind(keyword3);
	size_t position4 = arguments.rfind(keyword4);
	size_t position5 = arguments.find(EMPTY_SPACE_CHAR, position1 + 4, 1);
	size_t position6 = arguments.find(EMPTY_SPACE_CHAR, position2 + 4, 1);
	size_t position7 = arguments.find(EMPTY_SPACE_CHAR, position3 + 6, 1);

	bool isKeyword1Valid = false;
	bool isKeyword2Valid = false;
	bool isKeyword3Valid = false;

	string checkKeyword1 = EMPTY_STRING;
	string checkKeyword2 = EMPTY_STRING;
	string checkKeyword3 = EMPTY_STRING;

	if (position5 != string::npos) {
		checkKeyword1 = arguments.substr(position1 + 4, position5 - position1 - 4);

		if ((isParameterStringANumber(checkKeyword1) && checkKeyword1.size() == 6) ||
			isDateParameterValid(checkKeyword1)) {
			isKeyword1Valid = true;
		}
	}

	if (position6 != string::npos) {
		checkKeyword2 = arguments.substr(position2 + 4, position6 - position2 - 4);

		if (isParameterStringANumber(checkKeyword2) && checkKeyword2.size() == 4) {
			isKeyword2Valid = true;
		}
	}

	if (position7 != string::npos) {
		checkKeyword3 = arguments.substr(position3 + 6, position7 - position3 - 6);

		if (isParameterStringANumber(checkKeyword3) && checkKeyword3.size() == 4) {
			isKeyword3Valid = true;
		}
	}

	if ((isKeyword1Valid && isKeyword2Valid) || (isKeyword1Valid && isKeyword3Valid)) {
		if ((position1 > position2) || (position1 > position3)) {
			throw runtime_error(PARSER_SYNTAX_ERROR);
		}
	}
	else if (isKeyword2Valid && isKeyword3Valid) {
		throw runtime_error(PARSER_SYNTAX_ERROR);
	}
	else if (isKeyword1Valid && isKeyword2Valid && isKeyword3Valid) {
		throw runtime_error(PARSER_SYNTAX_ERROR);
	}
	else if (position4 == 0) {
		throw runtime_error(PARSER_SYNTAX_ERROR);
	}
	else {
	}
}
