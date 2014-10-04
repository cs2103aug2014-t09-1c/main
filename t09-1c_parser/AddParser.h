#pragma once
#ifndef ADD_PARSER
#define ADD_PARSER

#include "BaseClassParser.h"
#include "ParsedDataPackage.h"
#include <string>

#define ADD_PARSER_ERROR \
	"Unable to Commit. Please refer to \"help\" for guide to input."

using namespace std;

// Syntax: [eventName]<start><end><rating><@category> - timed
// Syntax: [eventName]<deadline><rating><@category> - deadline
// Syntax: [eventName]<rating><@category> - float
// Allowed overloads: event ((next)day of week or date) HHMM / event date HHMM to HHMM
// eg. Watch movie tomorrow / Watch movie next tuesday 1700 / watch movie next tuesday 1300 to 1500
// eg. Watch movie 191014 1700 to 1800

class AddParser :
	public BaseClassParser
{
private:
	ParsedDataPackage parsedData;

public:
	AddParser();
	~AddParser();
	ParsedDataPackage parseAndReturn(string parseInput);

	string argumentError();

	string extractLeadingBracketContent(string arguments);
	string nextArguments(string arguments);
	string extractDate(string arguments);
	void extractTime(string arguments);
	
};

#endif

