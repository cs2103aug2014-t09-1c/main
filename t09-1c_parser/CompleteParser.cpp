//@author A0108494Y
#include "stdafx.h"
#include "CompleteParser.h"

CompleteParser::CompleteParser() : BaseClassParser()
{
}

CompleteParser::~CompleteParser()
{
}

ParsedDataPackage CompleteParser::parseAndReturn(string parseInput)
{
	string inputWithWhiteSpaceRemoved = removeWhiteSpace(parseInput);
	string inputToLowerCase = toLowerCaseString(inputWithWhiteSpaceRemoved);
	string delimeter = COMPLETE_PARSE_KEYWORD_TO;

	if (inputToLowerCase.find(delimeter) != string::npos) {
		string firstLineNumber = inputToLowerCase.substr(0, inputToLowerCase.find(delimeter));

		if (isParameterStringANumber(firstLineNumber)) {
			insertAttribute(FROM_POSITION, stoi(firstLineNumber));
		}
		else {
			throw runtime_error(COMPLETE_PARSER_ERROR);
		}

		string secondLineNumber = inputToLowerCase;
		secondLineNumber.erase(0, inputToLowerCase.find(delimeter) + delimeter.length());

		if (isParameterStringANumber(secondLineNumber)) {
			insertAttribute(TO_POSITION, stoi(secondLineNumber));
		}
		else {
			throw runtime_error(COMPLETE_PARSER_ERROR);
		}

		return parsedData;
	}
	else if (isParameterStringANumber(inputWithWhiteSpaceRemoved)) {
		insertAttribute(FROM_POSITION, stoi(inputWithWhiteSpaceRemoved));
		insertAttribute(TO_POSITION, stoi(inputWithWhiteSpaceRemoved));

		return parsedData;
	}
	else {
		throw runtime_error(COMPLETE_PARSER_ERROR);
	}
}
