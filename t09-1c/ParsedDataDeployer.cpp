#include "stdafx.h"
#include "ParsedDataDeployer.h"


ParsedDataDeployer::ParsedDataDeployer()
{
}


ParsedDataDeployer::~ParsedDataDeployer()
{
}

void ParsedDataDeployer::executeAdd(ParsedDataPackage addPackage, string fileName)
{
	AddLogic newAdd(fileName);
	newAdd.appendToLineEntry("name", addPackage.name);
	newAdd.appendToLineEntry("rating", addPackage.rating);
	newAdd.appendToLineEntry("type", addPackage.type);
	newAdd.appendToLineEntry("category", addPackage.category);
	newAdd.appendToLineEntry("start", addPackage.start);
	newAdd.appendToLineEntry("end", addPackage.end);
	newAdd.commitAdd;
}