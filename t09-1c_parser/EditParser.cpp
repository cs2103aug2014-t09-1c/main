#include "stdafx.h"
#include "EditParser.h"
#include <algorithm>

EditParser::EditParser() : BaseClassParser()
{
}

EditParser::~EditParser()
{
}

void EditParser::getPositionNumber(string input)
{
	size_t position1 = input.find(DELIMETER_START);
	string positionNum = input.substr(0, position1);
	positionNum = removeWhiteSpace(positionNum);

	if (isParameterStringANumber(positionNum)) {
		insertAttribute(FROM_POSITION, stoi(positionNum));
	}
	else {
		throw runtime_error(EDIT_PARSER_ERROR);
	}
}

string EditParser::extractLeadingBracketContent(string arguments)
{
	string contents = EMPTY_STRING;
	size_t startingPosition = arguments.find(DELIMETER_START);
	size_t endingPosition = arguments.find(DELIMETER_END);

	if (startingPosition == string::npos || endingPosition == string::npos) {
		throw runtime_error(EDIT_PARSER_ERROR);

		return contents;
	}
	else {
		contents = arguments.substr(startingPosition + 1, endingPosition - startingPosition - 1);

		return contents;
	}
}

string EditParser::nextArguments(string argument)
{
	string delimiter = DELIMETER_END;
	argument.erase(0, argument.find(delimiter) + 1);

	return argument;
}

string EditParser::extractDate(string iterArguments)
{
	try{
		string date = extractLeadingBracketContent(iterArguments);
		string resultDate = getDate(date);

		return resultDate;
	}
	catch (const exception& ex) {
		throw runtime_error(ex.what());
	}
}

void EditParser::extractTime(string iterArguments)
{
	try {
		string time = extractLeadingBracketContent(iterArguments);
		getAndStoreTimes(time);
	}
	catch (const exception& ex) {
		throw runtime_error(ex.what());
	}
}

ParsedDataPackage EditParser::parseAndReturn(string parseInput)
{
	try {
		getPositionNumber(parseInput);
		insertAttribute(NAME_ATTRIBUTE, extractLeadingBracketContent(parseInput));
		parseInput = nextArguments(parseInput);
		insertAttribute(DATE_ATTRIBUTE, extractDate(parseInput));
		parseInput = nextArguments(parseInput);
		extractTime(parseInput);
		parseInput = nextArguments(parseInput);
		insertAttribute(CATEGORY_ATTRIBUTE, extractLeadingBracketContent(parseInput));

		return parsedData;
	}
	catch (const exception& ex) {
		throw runtime_error(ex.what());
	}
}

int EditParser::convertToPosition(string argument)
{
	int number = -1;
	argument.erase(remove_if(argument.begin(), argument.end(), isspace), argument.end());

	if (isParameterStringANumber(argument)) {
		number = std::stoi(argument);
	}

	return number;
}
