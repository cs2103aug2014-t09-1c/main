#pragma once
#ifndef COMPLETE_PARSER
#define COMPLETE_PARSER

#include "BaseClassParser.h"
#include "ParsedDataPackage.h"

#define COMPLETE_PARSER_ERROR \
	"Please enter the line number of the task you wish to mark as completed!"

using namespace std;

// Complete Syntax: complete 2

class CompleteParser :
	public BaseClassParser
{
private:
	int repetition = 1;
public:
	CompleteParser();
	~CompleteParser();

	ParsedDataPackage parseAndReturn(string parseInput);

	void setErrorString(string errorString);
	void setErrorTrue();
	bool isInputValid();
	void setRepetition(int numberForDeletion);
	int getRepetition();

};

#endif
