#pragma once
#include "BaseClassParser.h"
#include "ParsedDataPackage.h"

class EditParser :
	public BaseClassParser
{
private:
	string arguments;

public:
	EditParser();
	~EditParser();
	ParsedDataPackage parseAndReturn(string parseInput);

	void setArguments(string arguments);
};

