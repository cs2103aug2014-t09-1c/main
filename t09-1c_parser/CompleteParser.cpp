#include "stdafx.h"
#include "CompleteParser.h"
#include "ParserHelperFunctions.h"

CompleteParser::CompleteParser()
{
}


CompleteParser::~CompleteParser()
{
}

ParsedDataPackage CompleteParser::parseAndReturn(string parseInput)
{
	string removedWhiteSpace = ParserHelperFunctions::removeWhiteSpace(parseInput);
	size_t positionHyphen = removedWhiteSpace.find("-");

	if (ParserHelperFunctions::isParameterStringANumber(removedWhiteSpace)) 
	{	
		parsedData.lineNum = stoi(removedWhiteSpace);
	}
	else if (positionHyphen != string::npos)
	{
		string start = removedWhiteSpace.substr(0, positionHyphen);
		string end = removedWhiteSpace.substr(positionHyphen + 1);
		setRepetition(stoi(end) - stoi(start) + 1);
		parsedData.lineNum = stoi(start);
	}
	else {
		setErrorString(COMPLETE_PARSER_ERROR);
		setErrorTrue();
	}
	return parsedData;
}

void CompleteParser::setErrorString(string errorString)
{
	error = errorString;
}

void CompleteParser::setErrorTrue()
{
	errorPresent = true;
}

bool CompleteParser::isInputValid()
{
	return errorPresent;
}

void CompleteParser::setRepetition(int numberForCompletion)
{
	repetition = numberForCompletion;
}

int CompleteParser::getRepetition()
{
	return repetition;
}