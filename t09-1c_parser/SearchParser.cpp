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

string SearchParser::findCommandAndGetArgument(string iterarguments)
{
	string line = iterarguments;
	line = line.substr(7);
	string delimiter = " ";
	command = line.substr(0, line.find(delimiter));
	string argument = line.substr(line.find(delimiter)+1);
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
	string argument = findCommandAndGetArgument(parseInput);
	if (command == "date"){
		parsedData.date = extractDate(argument);
	}
	else if(command == "name"){
		parsedData.name = argument;
	}
	else if (command == "category"){
		parsedData.category = argument;
	}
	return parsedData;
}