#include "stdafx.h"
#include "BaseClassParser.h"
#include <algorithm>
#include <iostream>
#include <vector>


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