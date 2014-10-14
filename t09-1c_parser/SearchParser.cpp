#include "stdafx.h"
#include "SearchParser.h"
#include "TimeParser.h"
#include "ParserHelperFunctions.h"

// Syntax: search [event][date][category] 
// Syntax: search [event][][]
// Syntax: search [][date][]
// Syntax: search [][][category]
// or any 2 
//e.g. date > mon, 201214
SearchParser::SearchParser() : parsedData()
{
}


SearchParser::~SearchParser()
{
}

string AddParser::argumentError()
{
	return SEARCH_PARSER_ERROR;
}

string SearchParser::extractLine(string iterarguments)
{
	string lineNum = addObject.extractLeadingBracketContent(iterarguments);
}

string SearchParser::extractDate(string iterArguments)
{
	string date = extractLine(iterArguments);
	string noSpaceDate = ParserHelperFunctions::removeWhiteSpace(date);
	if (date.size() == 0) {
		return "";
	}
	else if (ParserHelperFunctions::isParameterStringANumber(noSpaceDate)) {

		if (noSpaceDate.length() == 6) {
			return TimeParser::formatDate(noSpaceDate);
		}
		else {
			argumentError();
		}
	}
	else {
		string newDateFormat = TimeParser::parseDayOfWeek(date);
		if (newDateFormat != date) { //parseDayOfWeek returns unchanged if error
			return newDateFormat;
		}
		else {
			argumentError();
		}
	}
}
string SearchParser::nextArguments(string argument)
{
	string delimiter = "]";
	argument.erase(0, argument.find(delimiter) + 1);
	return argument;
}

ParsedDataPackage SearchParser::parseAndReturn(string parseInput)
{
	parsedData.name = extractLine(parseInput);
	parseInput = nextArguments(parseInput);
	parsedData.date = extractDate(parseInput);
	parseInput = nextArguments(parseInput);
	parsedData.category = extractLine(parseInput);

	return parsedData;
}