#include "stdafx.h"
#include "LogicHelperFunctions.h"


LogicHelperFunctions::LogicHelperFunctions()
{
}


LogicHelperFunctions::~LogicHelperFunctions()
{
}

string LogicHelperFunctions::toLowerCaseString(string input)
{
	transform(input.begin(), input.end(), input.begin(), ::tolower);
	return input;
}