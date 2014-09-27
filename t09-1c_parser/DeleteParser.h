#pragma once
#include "BaseClassParser.h"
#include "ParsedDataPackage.h"

class DeleteParser :
	public BaseClassParser
{
private:
	string arguments;

public:
	DeleteParser();
	~DeleteParser();
	ParsedDataPackage parseAndReturn(string parseInput);

	void setArguments(string arguments);
};

