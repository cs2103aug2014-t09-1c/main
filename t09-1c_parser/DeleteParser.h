#pragma once
#include "BaseClassParser.h"
class DeleteParser :
	public BaseClassParser
{
public:
	DeleteParser();
	~DeleteParser();
	ParsedDataPackage parseAndReturn(string parseInput);
};

