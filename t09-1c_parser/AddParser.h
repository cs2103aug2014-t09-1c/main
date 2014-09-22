#pragma once
#include "BaseClassParser.h"
#include "ParsedDataPackage.h"

class AddParser :
	public BaseClassParser
{
public:
	AddParser();
	~AddParser();
	ParsedDataPackage parseAndReturn(string parseInput);

	void processArguments(string arguments);
};

