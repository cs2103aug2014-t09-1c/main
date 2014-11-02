#pragma once
#ifndef EDIT_PARSER
#define EDIT_PARSER

#include "BaseClassParser.h"

#define EDIT_PARSER_ERROR \
	"Unable to Commit. Please refer to \"help\" for guide to input."

using namespace std;

class EditParser :
	public BaseClassParser
{
private:
	string extractLeadingBracketContent(string arguments);
	string nextArguments(string arguments);
	string extractDate(string arguments);
	void extractTime(string arguments);
	void getPositionNumber(string input);

public:
	EditParser();
	~EditParser();
	ParsedDataPackage parseAndReturn(string parseInput);


	int convertToPosition(string argument);
};

#endif

