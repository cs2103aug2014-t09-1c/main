#include "stdafx.h"
#include "DeleteParser.h"
#include "ParserHelperFunctions.h"

// Syntax: [eventName][date][start-end][category] - timed
// Syntax: [eventName][date][deadline][category] - deadline
// Syntax: [eventName][][][category] - float
// category is to be made optional. 
// ie syntax can just be  [eventName][][][]
// Allowed overloads: event ((next)day of week or date) HHMM / event date HHMM to HHMM
// eg. Watch movie tomorrow / Watch movie next tuesday 1700 / watch movie next tuesday 1300 to 1500
// eg. Watch movie 191014 1700 to 1800

// Delete Syntax: delete [010914][2] or delete [3]

DeleteParser::DeleteParser()
{
}


DeleteParser::~DeleteParser()
{
}

string DeleteParser::argumentError()
{
	return DELETE_PARSER_ERROR;
}

void DeleteParser::extractLine(string iterArguments)
{
	string lineNum = add.extractLeadingBracketContent(iterArguments);

	if (ParserHelperFunctions::isParameterStringANumber(lineNum)) {
		parsedData.lineNum = stoi(lineNum);
	}
	else {
		setErrorString(DELETE_PARSER_LINE_NUM_ERROR);
		setErrorTrue();
	}
}

ParsedDataPackage DeleteParser::parseAndReturn(string parseInput)
{
	{
		string delimiter = "[";
		string getFirst = ParserHelperFunctions::removeWhiteSpace(parseInput.substr(0, parseInput.find(delimiter)));
		size_t positionHyphen = getFirst.find("-");//

		if (ParserHelperFunctions::isParameterStringANumber(getFirst)) {
			int lineNum = stoi(getFirst);
			parsedData.lineNum = lineNum;
			parseInput.erase(0, parseInput.find(delimiter));
			excessInput = parseInput;
		}
		else if (positionHyphen != string::npos)
		{
			string start = getFirst.substr(0, positionHyphen);
			string end = getFirst.substr(positionHyphen + 1);
			if (!ParserHelperFunctions::isParameterStringANumber(start)){
				setErrorString(DELETE_PARSER_LINE_NUM_ERROR);
				setErrorTrue();
				return parsedData;
			}
			if (!ParserHelperFunctions::isParameterStringANumber(end)){
				end = start;
			}
			setRepetition(stoi(end) - stoi(start) + 1);
			parsedData.lineNum = stoi(start);
		}
		else {
			parsedData.date = add.extractDate(parseInput);
			parseInput = add.nextArguments(parseInput);
			extractLine(parseInput);
			excessInput = add.nextArguments(parseInput);
		}

		return parsedData;
	}
}
void DeleteParser::setErrorString(string errorString)
{
	error = errorString;
}

void DeleteParser::setErrorTrue()
{
	errorPresent = true;
}

bool DeleteParser::isInputValid()
{
	return errorPresent;
}

string DeleteParser::getErrorString()
{
	return error;
}

void DeleteParser::setRepetition(int numberForDeletion)
{
	repetition = numberForDeletion;
}

int DeleteParser::getRepetition()
{
	return repetition;
}