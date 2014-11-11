//@author A0111718M
#include "stdafx.h"
#include "AddParser.h"

// Syntax: [eventName][date][start-end][category] - timed
// Syntax: [eventName][date][deadline][category] - deadline
// Syntax: [eventName][][][category] - float
// category is to be made optional. 
// ie syntax can just be  [eventName][][][]

// Allowed overloads: event ((next)day of week or date) HHMM / event date HHMM to HHMM
// eg. Watch movie on tomorrow / Watch movie on next tuesday at 1700 / watch movie on next tuesday from 1300 to 1500
// eg. Watch movie on 1910140 from 1700 to 1800

//@ERIC A0111718M
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
	string contents = EMPTY_STRING;
	size_t position1 = arguments.find(DELIMETER_START);
	size_t position2 = arguments.find(DELIMETER_END);

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
	string delimiter = DELIMETER_END;
	argument.erase(0, argument.find(delimiter) + 1);

	return argument;
}

string AddParser::extractDate(string iterArguments)
{
	try{
		string dateExtracted = extractLeadingBracketContent(iterArguments);
		string resultDate = getDate(dateExtracted);

		return resultDate;
	}
	catch (const exception& ex) {
		throw runtime_error(ex.what());
	}
}

void AddParser::extractTime(string iterArguments)
{
	try {
		string timeExtracted = extractLeadingBracketContent(iterArguments);
		getAndStoreTimes(timeExtracted);
	}
	catch (const exception& ex) {
		throw runtime_error(ex.what());
	}
}

ParsedDataPackage AddParser::parseAndReturn(string parseEntry)
{
	try {
		insertAttribute(NAME_ATTRIBUTE, extractLeadingBracketContent(parseEntry));
		parseEntry = nextArguments(parseEntry);
		insertAttribute(DATE_ATTRIBUTE, extractDate(parseEntry));
		parseEntry = nextArguments(parseEntry);
		extractTime(parseEntry);
		parseEntry = nextArguments(parseEntry);
		insertAttribute(CATEGORY_ATTRIBUTE, extractLeadingBracketContent(parseEntry));

		return parsedData;
	}
	catch (const exception& ex) {
		throw runtime_error(ex.what());
	}
}

ParsedDataPackage AddParser::parseNLAndReturn(string parseEntry)
{
	try {
		insertAttribute(CATEGORY_ATTRIBUTE, extractCategoryNL(parseEntry));
		parseEntry = removeCategoryNL(parseEntry);
		insertAttribute(NAME_ATTRIBUTE, extractEventNL(parseEntry));
		insertAttribute(DATE_ATTRIBUTE, extractDateNL(parseEntry));
		extractTimesNL(parseEntry);
		syntaxSwapChecker(parseEntry);

		return parsedData;
	}
	catch (const exception& ex) {
		throw runtime_error(ex.what());
	}
}

string AddParser::extractCategoryNL(string arguments)
{
	string category = EMPTY_STRING;
	string categoryKeyword = CATEGORY_KEYWORD;
	size_t position1 = arguments.rfind(categoryKeyword);

	if (position1 != string::npos) {
		category = arguments.substr(position1 + 1);

		return category;
	}
	else {
		return category;
	}
}

string AddParser::removeCategoryNL(string arguments)
{
	string CategoryKeyword = CATEGORY_KEYWORD;
	size_t position1 = arguments.rfind(CategoryKeyword);

	if (position1 != string::npos) {
		string newArguments = arguments.substr(0, position1 - 1);

		return newArguments;
	}
	else {
		return arguments;
	}
}

string AddParser::extractEventNL(string arguments)
{
	try {
		string event = getEventNL(arguments);

		return event;
	}
	catch (const exception& ex) {
		throw runtime_error(ex.what());
	}
}

string AddParser::extractDateNL(string arguments)
{
	try {
		string date = getDateNL(arguments);

		return date;
	}
	catch (const exception& ex) {
		throw runtime_error(ex.what());
	}
}

void AddParser::extractTimesNL(string arguments)
{
	try {
		getAndStoreTimesNL(arguments);
	}
	catch (const exception& ex) {
		throw runtime_error(ex.what());
	}
}

void AddParser::syntaxSwapChecker(string arguments)
{
	try {
		checkForSyntaxSwap(arguments);
	}
	catch (const exception& ex) {
		throw runtime_error(ex.what());
	}
}
