#include "stdafx.h"
#include "ParserHelperFunctions.h"
#include <unordered_set>


ParserHelperFunctions::ParserHelperFunctions()
{
}


ParserHelperFunctions::~ParserHelperFunctions()
{
}

string ParserHelperFunctions::toLowerCaseString(string input)
{
	transform(input.begin(), input.end(), input.begin(), ::tolower);
	return input;
}

int ParserHelperFunctions::findMatchingStringIndex(string str, vector<string> lst)
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

bool ParserHelperFunctions::isParameterStringEmpty(string parameter)
{
	return parameter.find_first_not_of(' ') == std::string::npos;
}

bool ParserHelperFunctions::isParameterStringANumber(string parameter)
{
	if (isParameterStringEmpty(parameter)) {
		return false;
	}
	else {
		return parameter.find_first_not_of("0123456789") == std::string::npos;
	}
}

string ParserHelperFunctions::removeWhiteSpace(string parameter)
{
	parameter.erase(remove(parameter.begin(), parameter.end(), ' '), parameter.end());
	return parameter;
}

bool ParserHelperFunctions::isDayValid(string day)
{
	unordered_set<string> set = { "mon", "tues", "wed", "thurs", "fri",
		"monday", "tuesday", "wednesday", "thursday", "friday" };

	unordered_set<string>::const_iterator got = set.find(day);

	if (got == set.end()) {
		return false;
	}
	else {
		return true;
	}
}