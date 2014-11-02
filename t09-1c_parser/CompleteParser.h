#pragma once
#ifndef COMPLETE_PARSER
#define COMPLETE_PARSER

#include "BaseClassParser.h"
#include "ParsedDataPackage.h"

#define COMPLETE_PARSER_ERROR \
	"Please enter valid <from> and <to> line numbers"

#define DELIMETER \
	"to"

using namespace std;

// Complete Syntax: complete 2

class CompleteParser :
	public BaseClassParser
{
private:

public:
	CompleteParser();
	~CompleteParser();

	ParsedDataPackage parseAndReturn(string parseInput);
	
};

#endif
