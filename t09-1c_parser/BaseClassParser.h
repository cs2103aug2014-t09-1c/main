#pragma once
#include "ParsedDataPackage.h"
class BaseClassParser
{
protected:
	ParsedDataPackage parsedData;
	string error;
	bool errorPresent;
	BaseClassParser();
	~BaseClassParser();

};

