#pragma once
#include "BaseClassParser.h"
#include "ParsedDataPackage.h"

class DeleteParser :
	public BaseClassParser
{
public:
	DeleteParser();
	~DeleteParser();
	ParsedDataPackage parseAndReturn(string parseInput);

	void processArguments(string arguments);
};

