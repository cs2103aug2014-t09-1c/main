#pragma once
#ifndef COMPLETE_PARSER
#define COMPLETE_PARSER

#include "BaseClassParser.h"

// Complete Syntax: complete 2

#define COMPLETE_PARSER_ERROR \
	"Please enter valid <from> and <to> line numbers"

using namespace std;

class CompleteParser :
	public BaseClassParser
{
public:
	CompleteParser();
	~CompleteParser();

	ParsedDataPackage parseAndReturn(string parseInput);
	
};

#endif
