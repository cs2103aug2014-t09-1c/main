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
	string inputWhiteSpaceRemoved = removeWhiteSpace(parseInput);
	string inputtoLowerCase = toLowerCaseString(inputWhiteSpaceRemoved);
	string delimeter = DELETE_PARSE_KEYWORD_TO;

	if (inputtoLowerCase.find(delimeter) != string::npos) {
		string firstLineNumber = inputtoLowerCase.substr(0, inputtoLowerCase.find(delimeter));

		if (isParameterStringANumber(firstLineNumber)) {
			insertAttribute(FROM_POSITION, stoi(firstLineNumber));
		}
		else {
			throw runtime_error(DELETE_PARSER_ERROR);
		}

		string secondLineNumber = inputtoLowerCase;
		secondLineNumber.erase(0, inputtoLowerCase.find(delimeter) + delimeter.length());

		if (isParameterStringANumber(secondLineNumber)) {
			insertAttribute(TO_POSITION, stoi(secondLineNumber));
		}
		else {
			throw runtime_error(DELETE_PARSER_ERROR);
		}

		return parsedData;
	}
	else if (isParameterStringANumber(inputWhiteSpaceRemoved)) {
		insertAttribute(FROM_POSITION, stoi(inputWhiteSpaceRemoved));
		insertAttribute(TO_POSITION, stoi(inputWhiteSpaceRemoved));

		return parsedData;
	}
	else {
		throw runtime_error(DELETE_PARSER_ERROR);
	}
}
