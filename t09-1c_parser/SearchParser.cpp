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
		checkTimeisRangeFormat(time);
		getAndStoreTimes(time);
	}
	catch (const exception& ex) {
		throw runtime_error(ex.what());
	}
}

string SearchParser::parseSearchArgs(string parseEntry)
{
	string checkInput = parseDayOfWeek(parseEntry);

	if (isParameterStringANumber(checkInput) && checkInput.length() == 4) {
		checkInput.insert(2, TIME_INSERT_COLON);
	}

	return checkInput;
}

void SearchParser::checkTimeisRangeFormat(string entry)
{
	if (entry.size() < 9) {
		throw runtime_error(FREE_SLOT_RANGE_ERROR);
	}
}

void SearchParser::checkDurationisValid(string entry)
{
	string entryWhiteSpaceRemoved = removeWhiteSpace(entry);
	if (!isParameterStringANumber(entryWhiteSpaceRemoved) && entryWhiteSpaceRemoved.size() != 4) {
		throw runtime_error(FREE_SLOT_DURATION_ERROR);
	}
}

void SearchParser::getDuration(string entry)
{
	const int maxHourDuration = 23;
	const int maxMinDuration = 59;
	const int HHMMLength = 2;

	try {
		string duration = extractLeadingBracketContent(entry);
		checkDurationisValid(duration);
		int hourDuration = stoi(duration.substr(0, HHMMLength));
		int minDuration = stoi(duration.substr(2, HHMMLength));
		if (hourDuration > maxHourDuration || minDuration > maxMinDuration) {
			throw runtime_error(FREE_SLOT_LONG_DURATION_ERROR);
		}
		insertAttribute(FROM_POSITION, hourDuration);
		insertAttribute(TO_POSITION, minDuration);
	}
	catch (const exception& ex) {
		throw runtime_error(ex.what());
	}
}

ParsedDataPackage SearchParser::parsefreeSlotCheck(string entry)
{
	try{
		insertAttribute(DATE_ATTRIBUTE,extractDate(entry));
		entry = nextArguments(entry);
		extractTime(entry);
		entry = nextArguments(entry);
		getDuration(entry);
		return parsedData;
	}
	catch (const exception& ex) {
		throw runtime_error(ex.what());
	}
}