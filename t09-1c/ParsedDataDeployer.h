#pragma once
#ifndef PARSE_DATA_DEPLOYER
#define PARSE_DATA_DEPLOYER

#include "ParsedDataPackage.h"
#include "AddLogic.h"
#include "DeleteLogic.h"
#include "EditLogic.h"

class ParsedDataDeployer
{
public:
	ParsedDataDeployer();
	~ParsedDataDeployer();
	static void executeAdd(ParsedDataPackage addPackage, FileLogic fileHandler);
	static void executeDelete(ParsedDataPackage deletePackage, FileLogic fileHandler);
	static void executeEdit(vector<ParsedDataPackage> editPackages, FileLogic fileHandler);
};
#endif