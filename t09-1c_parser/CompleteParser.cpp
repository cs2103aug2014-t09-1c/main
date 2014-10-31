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
	if (ParserHelperFunctions::isParameterStringANumber(removedWhiteSpace)) {
		parsedData.lineNum = stoi(removedWhiteSpace);
		return parsedData;
	}
	else {
		setErrorString(COMPLETE_PARSER_ERROR);
		setErrorTrue();
		return parsedData;
	}
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