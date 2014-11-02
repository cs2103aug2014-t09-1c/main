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
	string removedWhiteSpace = removeWhiteSpace(parseInput);
	string toLowerCase = toLowerCaseString(removedWhiteSpace);
	string delimeter = DELIMETER;
	if (toLowerCase.find(delimeter) != string::npos) {
		string firstNum = toLowerCase.substr(0, toLowerCase.find(delimeter));
		if (isParameterStringANumber(firstNum)) {
			insertAttribute(FROM_POSITION,stoi(firstNum));
		}
		else{
			throw runtime_error(COMPLETE_PARSER_ERROR);
		}
		string secondNum = toLowerCase;
		secondNum.erase(0, toLowerCase.find(delimeter) + delimeter.length());
		if (isParameterStringANumber(secondNum)) {
			insertAttribute(TO_POSITION, stoi(secondNum));
		}
		else{
			throw runtime_error(COMPLETE_PARSER_ERROR);
		}
		return parsedData;
	}
	else if (isParameterStringANumber(removedWhiteSpace)) {
		insertAttribute(FROM_POSITION, stoi(removedWhiteSpace));
		insertAttribute(TO_POSITION, stoi(removedWhiteSpace));
		return parsedData;
	}
	else {
		throw runtime_error(COMPLETE_PARSER_ERROR);
	}
}