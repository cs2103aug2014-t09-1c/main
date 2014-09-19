#include "stdafx.h"
#include "VariableHelperFunctions.h"


VariableHelperFunctions::VariableHelperFunctions()
{
}


VariableHelperFunctions::~VariableHelperFunctions()
{
}

bool VariableHelperFunctions::isParameterStringEmpty(string parameter)
{
	return parameter.find_first_not_of(' ') == std::string::npos;
}

bool VariableHelperFunctions::isParameterStringANumber(string parameter)
{
	if (isParameterStringEmpty(parameter)) {
		return false;
	}
	else {
		return parameter.find_first_not_of("+-.0123456789") == std::string::npos;
	}
}

int VariableHelperFunctions::convertStringToInt(string argument)
{
	int stringInInt = stoi(argument);
	return stringInInt;
}

bool VariableHelperFunctions::checkTwoStringsAlphabeticalPriority(const string& first, const string& second)
{
	unsigned int letterPosition = 0;
	while ((letterPosition < first.length()) && (letterPosition < second.length()))
	{
		if (tolower(first[letterPosition]) < tolower(second[letterPosition])) {
			return true;
		}
		else if (tolower(first[letterPosition]) > tolower(second[letterPosition])) {
			return false;
		}
		++letterPosition;
	}
	return (first.length() < second.length());
}

list<string> VariableHelperFunctions::arrangeAlphabeticallyStrings(list<string> stringList)
{
	stringList.sort(VariableHelperFunctions::checkTwoStringsAlphabeticalPriority);
	return stringList;
}

string VariableHelperFunctions::toLowerCaseString(string input)
{
	transform(input.begin(), input.end(), input.begin(), ::tolower);
	return input;
}

bool VariableHelperFunctions::checkIfKeywordIsInString(string keyword, string inputString)
{
	keyword = toLowerCaseString(keyword);
	inputString = toLowerCaseString(inputString);
	size_t foundKeywordAt = inputString.find(keyword);
	if (foundKeywordAt != std::string::npos) {
		return true;
	}
	else { return false; }
}