#pragma once
#include "ParsedDataPackage.h"
class BaseClassParser
{
protected:
	ParsedDataPackage parsedData;
	BaseClassParser();
	~BaseClassParser();
	virtual ParsedDataPackage parseAndReturn(string parseInput);
};

