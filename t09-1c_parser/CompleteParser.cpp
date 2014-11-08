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
	string InputWithWhiteSpaceRemoved = removeWhiteSpace(parseInput);
	string InputToLowerCase = toLowerCaseString(InputWithWhiteSpaceRemoved);
	string delimeter = DELIMETER;
	if (InputToLowerCase.find(delimeter) != string::npos) {
		string FirstLineNumber = InputToLowerCase.substr(0, InputToLowerCase.find(delimeter));
		if (isParameterStringANumber(FirstLineNumber)) {
			insertAttribute(FROM_POSITION,stoi(FirstLineNumber));
		}
		else{
			throw runtime_error(COMPLETE_PARSER_ERROR);
		}
		string SecondLineNumber = InputToLowerCase;
		SecondLineNumber.erase(0, InputToLowerCase.find(delimeter) + delimeter.length());
		if (isParameterStringANumber(SecondLineNumber)) {
			insertAttribute(TO_POSITION, stoi(SecondLineNumber));
		}
		else{
			throw runtime_error(COMPLETE_PARSER_ERROR);
		}
		return parsedData;
	}
	else if (isParameterStringANumber(InputWithWhiteSpaceRemoved)) {
		insertAttribute(FROM_POSITION, stoi(InputWithWhiteSpaceRemoved));
		insertAttribute(TO_POSITION, stoi(InputWithWhiteSpaceRemoved));
		return parsedData;
	}
	else {
		throw runtime_error(COMPLETE_PARSER_ERROR);
	}
}