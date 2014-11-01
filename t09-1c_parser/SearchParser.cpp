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

string SearchParser::parseSearchArgs(string parseInput)
{
	string checkInput = parseDayOfWeek(parseInput);
	if (isParameterStringANumber(checkInput) && checkInput.length() == 4) {
		checkInput.insert(2, ":");
	}
	return checkInput;
}