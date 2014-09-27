#include "stdafx.h"
#include "ParserHelperFunctions.h"


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
	for (int i = 0; i < lst.size(); ++i) {
		if (lst[i] == str) {
			index = i;
			break;
		}
	}
	return index;
}