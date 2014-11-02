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
	size_t position1 = input.find("[");
	string pos = input.substr(0, position1);
	pos = removeWhiteSpace(pos);
	if (isParameterStringANumber(pos)) {
		insertAttribute(FROM_POSITION, stoi(pos));
	}
	else {
		throw runtime_error(EDIT_PARSER_ERROR);
	}
}

string EditParser::extractLeadingBracketContent(string arguments)
{
	string contents = "";
	size_t position1 = arguments.find("[");
	size_t position2 = arguments.find("]");

	if (position1 == string::npos || position2 == string::npos) {
		throw runtime_error(EDIT_PARSER_ERROR);
		return contents;
	}
	else {
		contents = arguments.substr(position1 + 1, position2 - position1 - 1);
		return contents;
	}
}

string EditParser::nextArguments(string argument)
{
	string delimiter = "]";
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
	catch (const exception& ex){
		throw runtime_error(ex.what());
	}
}

void EditParser::extractTime(string iterArguments)
{
	try {
		string time = extractLeadingBracketContent(iterArguments);
		getAndStoreTimes(time);
	}
	catch (const exception& ex){
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
	catch (const exception& ex){
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