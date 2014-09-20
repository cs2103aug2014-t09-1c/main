#pragma once
#include "BaseClassParser.h"
class EditParser :
	public BaseClassParser
{
public:
	EditParser();
	~EditParser();
	ParsedDataPackage parseAndReturn(string parseInput);
};

