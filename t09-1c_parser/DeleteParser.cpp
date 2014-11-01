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
	string removedWhiteSpace = removeWhiteSpace(parseInput);
	string toLowerCase = toLowerCaseString(parseInput);
	string delimeter = DELIMETER;
	if (toLowerCase.find(delimeter) != string::npos) {
		string firstNum = toLowerCase.substr(0, toLowerCase.find(delimeter));
		if (isParameterStringANumber(firstNum)) {
			insertAttribute(FROM_POSITION, stoi(firstNum));
		}
		else{
			throw runtime_error(DELETE_PARSER_ERROR);
		}
		string secondNum = firstNum;
		secondNum.erase(0, toLowerCase.find(delimeter));
		if (isParameterStringANumber(secondNum)) {
			insertAttribute(TO_POSITION, stoi(firstNum));
		}
		else{
			throw runtime_error(DELETE_PARSER_ERROR);
		}
	}
	if (isParameterStringANumber(removedWhiteSpace)) {
		insertAttribute(FROM_POSITION, stoi(removedWhiteSpace));
		insertAttribute(TO_POSITION, stoi(removedWhiteSpace));
		return parsedData;
	}
	else {
		throw runtime_error(DELETE_PARSER_ERROR);
	}
}