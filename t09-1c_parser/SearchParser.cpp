#include "stdafx.h"
#include "SearchParser.h"

// Syntax: search searchcategory item 
//e.g. search date 121012, search name annual concert, search category meeting


SearchParser::SearchParser() : BaseClassParser()
{
}

SearchParser::~SearchParser()
{
}

string SearchParser::extractLeadingBracketContent(string arguments)
{
	string contents = EMPTY_STRING;
	size_t startingPosition = arguments.find(DELIMETER_START);
	size_t endingPosition = arguments.find(DELIMETER_END);

	if (startingPosition == string::npos || endingPosition == string::npos) {
		return contents;
	}
	else {
		contents = arguments.substr(startingPosition + 1, endingPosition - startingPosition - 1);

		return contents;
	}
}

string SearchParser::nextArguments(string argument)
{
	string delimiter = DELIMETER_END;
	argument.erase(0, argument.find(delimiter) + 1);

	return argument;
}

string SearchParser::extractDate(string iterArguments)
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

void SearchParser::extractTime(string iterArguments)
{
	try {
		string time = extractLeadingBracketContent(iterArguments);
		checkTimeisRange(time);
		getAndStoreTimes(time);
	}
	catch (const exception& ex) {
		throw runtime_error(ex.what());
	}
}

string SearchParser::parseSearchArgs(string parseInput)
{
	string checkInput = parseDayOfWeek(parseInput);

	if (isParameterStringANumber(checkInput) && checkInput.length() == 4) {
		checkInput.insert(2, TIME_INSERT_COLON);
	}

	return checkInput;
}

void SearchParser::checkTimeisRange(string input)
{
	if (input.size() < 9) {
		throw runtime_error(FREE_SLOT_RANGE_ERROR);
	}
}

void SearchParser::checkDurationisValid(string input)
{
	string checkInput = removeWhiteSpace(input);

	if (!isParameterStringANumber(checkInput) && checkInput.size() != 4) {
		throw runtime_error(FREE_SLOT_DURATION_ERROR);
	}
}

void SearchParser::getDuration(string input)
{
	try {
		string duration = extractLeadingBracketContent(input);
		checkDurationisValid(duration);
		insertAttribute(FROM_POSITION, stoi(duration.substr(0, 2)));
		insertAttribute(TO_POSITION, stoi(duration.substr(2, 2)));
	}
	catch (const exception& ex) {
		throw runtime_error(ex.what());
	}
}

ParsedDataPackage SearchParser::parsefreeSlotCheck(string input)
{
	try{
		insertAttribute(DATE_ATTRIBUTE,extractDate(input));
		input = nextArguments(input);
		extractTime(input);
		input = nextArguments(input);
		getDuration(input);

		return parsedData;
	}
	catch (const exception& ex) {
		throw runtime_error(ex.what());
	}
}
