#pragma once
#include "BaseClassParser.h"
#include "ParsedDataPackage.h"

class EditParser :
	public BaseClassParser
{
public:
	EditParser();
	~EditParser();
	ParsedDataPackage parseAndReturn(string parseInput);

	void processArguments(string arguments);
};

