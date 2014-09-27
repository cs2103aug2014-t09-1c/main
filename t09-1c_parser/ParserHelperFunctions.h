#pragma once
#ifndef PARSER_HELPER_FUNCTIONS
#define PARSER_HELPER_FUNCTIONS

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class ParserHelperFunctions
{
protected:
	ParserHelperFunctions();
	~ParserHelperFunctions();

public:
	static string toLowerCaseString(string input);
	static int findMatchingStringIndex(string str, vector<string> lst);
};

#endif

