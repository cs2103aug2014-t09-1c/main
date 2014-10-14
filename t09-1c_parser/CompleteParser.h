#pragma once
#ifndef COMPLETE_PARSER
#define COMPLETE_PARSER

#include "BaseClassParser.h"
#include "ParsedDataPackage.h"

#define COMPLETE_PARSER_ERROR \
	"Unable to Commit. Please refer to \"help\" for guide to input."

using namespace std;

// Complete Syntax: complete 2

class CompleteParser :
	public BaseClassParser
{
public:
	CompleteParser();
	~CompleteParser();

	ParsedDataPackage parseAndReturn(string parseInput);

	void setErrorString(string errorString);
	void setErrorTrue();
	bool isInputValid();

};

#endif
