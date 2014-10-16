#include "stdafx.h"
#include "SearchParser.h"
#include "TimeParser.h"
#include "ParserHelperFunctions.h"

// Syntax: search searchcategory item 
//e.g. search date 121012, search name annual concert, search category meeting
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

string SearchParser::findTypeAndGetArgument(string typeAndArgument)
{
	string line = typeAndArgument;
	string delimiter = " ";
	type = line.substr(0, line.find(delimiter));
	line = line.substr(line.find(delimiter) + 1);
	string argument = line.substr(line.find_first_not_of(' '));
	return argument;
}

string SearchParser::extractDate(string argument)
{
	string date = argument;
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
/*string SearchParser::nextArguments(string argument)
{
	string delimiter = "]";
	argument.erase(0, argument.find(delimiter) + 1);
	return argument;
}*/

ParsedDataPackage SearchParser::parseAndReturn(string parseInput)
{
	string argument = findTypeAndGetArgument(parseInput);
	if (type == "date"){
		parsedData.date = extractDate(argument);
	}
	else if(type == "name"){
		parsedData.name = argument;
	}
	else if (type == "category"){
		parsedData.category = argument;
	}
	return parsedData;
}