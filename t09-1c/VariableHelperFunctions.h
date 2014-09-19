#pragma once
#include <vector>
#include <algorithm> 
#include <list>
#include <cctype>
#include <sstream>
#include "stdafx.h"

using namespace std;

class VariableHelperFunctions
{
private:
	VariableHelperFunctions();
	~VariableHelperFunctions();
public:
	//string helper methods
	static bool checkTwoStringsAlphabeticalPriority(const string& first, const string& second);
	static list<string> arrangeAlphabeticallyStrings(list<string> toBeArranged);
	static bool isParameterStringEmpty(string parameter);
	static string toLowerCaseString(string input);
	static bool checkIfKeywordIsInString(string keyword, string inputString);
	//int helper methods
	static bool isParameterStringANumber(string parameter);
	static int convertStringToInt(string argument);
	
	
};

