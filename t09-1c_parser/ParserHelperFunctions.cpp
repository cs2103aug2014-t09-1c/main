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
