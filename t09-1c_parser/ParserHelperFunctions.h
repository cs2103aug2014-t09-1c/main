#pragma once
#ifndef PARSER_HELPER_FUNCTIONS
#define PARSER_HELPER_FUNCTIONS

#include <algorithm>
#include <iostream>

using namespace std;

class ParserHelperFunctions
{
protected:
	ParserHelperFunctions();
	~ParserHelperFunctions();

public:
	string toLowerCaseString(string input);
};

#endif

