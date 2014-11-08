#include "stdafx.h"
#include "DeleteParser.h"

DeleteParser::DeleteParser() : BaseClassParser()
{
}


DeleteParser::~DeleteParser()
{
}

ParsedDataPackage DeleteParser::parseAndReturn(string parseInput)
{
	string InputWhiteSpaceRemoved = removeWhiteSpace(parseInput);
	string InputtoLowerCase = toLowerCaseString(InputWhiteSpaceRemoved);
	string delimeter = DELIMETER;
	if (InputtoLowerCase.find(delimeter) != string::npos) {
		string FirstLineNumber = InputtoLowerCase.substr(0, InputtoLowerCase.find(delimeter));
		if (isParameterStringANumber(FirstLineNumber)) {
			insertAttribute(FROM_POSITION, stoi(FirstLineNumber));
		}
		else{
			throw runtime_error(DELETE_PARSER_ERROR);
		}
		string SecondLineNumber = InputtoLowerCase;
		SecondLineNumber.erase(0, InputtoLowerCase.find(delimeter) + delimeter.length());
		if (isParameterStringANumber(SecondLineNumber)) {
			insertAttribute(TO_POSITION, stoi(SecondLineNumber));
		}
		else{
			throw runtime_error(DELETE_PARSER_ERROR);
		}
		return parsedData;
	}
	else if (isParameterStringANumber(InputWhiteSpaceRemoved)) {
		insertAttribute(FROM_POSITION, stoi(InputWhiteSpaceRemoved));
		insertAttribute(TO_POSITION, stoi(InputWhiteSpaceRemoved));
		return parsedData;
	}
	else {
		throw runtime_error(DELETE_PARSER_ERROR);
	}
}