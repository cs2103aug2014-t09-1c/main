#pragma once
#ifndef DELETE_PARSER
#define DELETE_PARSER

#include "BaseClassParser.h"

#define DELETE_PARSER_ERROR \
	"Unable to Commit. Please refer to \"help\" for guide to input."
#define DELETE_PARSER_LINE_NUM_ERROR \
	"Please enter valid <from> and <to> line numbers"
#define DELIMETER \
	"to"

class DeleteParser :
	public BaseClassParser
{

public:
	DeleteParser();
	~DeleteParser();

	ParsedDataPackage parseAndReturn(string parseInput);
};

#endif