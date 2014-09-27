#pragma once
#include "BaseClassParser.h"
#include "ParsedDataPackage.h"
#include <string>

using namespace std;

// Syntax: [eventName] <start> <end> <rating> <@category@>

class AddParser :
	public BaseClassParser
{
private:
	string arguments;

public:
	AddParser();
	~AddParser();
	ParsedDataPackage parseAndReturn(string parseInput);

	string argumentError();

	void setArguments(string input);
	string extractEventName(string arguments);
	string extractStart(string arguments);
	string extractEnd(string arguments);
	string extractRating(string arguments);
	string extractCategory(string arguemts);
};

