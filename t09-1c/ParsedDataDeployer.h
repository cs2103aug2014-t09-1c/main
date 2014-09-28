#pragma once
#ifndef PARSE_DATA_DEPLOYER
#define PARSE_DATA_DEPLOYER

#include <ParsedDataPackage.h>
#include <AddLogic.h>

class ParsedDataDeployer
{
public:
	ParsedDataDeployer();
	~ParsedDataDeployer();
	static void executeAdd(ParsedDataPackage addPackage, string fileName);
};
#endif