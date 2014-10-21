#pragma once
#ifndef PARSE_DATA_DEPLOYER
#define PARSE_DATA_DEPLOYER

#include "ParsedDataPackage.h"
#include "AddLogic.h"
#include "DeleteLogic.h"
#include "EditLogic.h"
#include "SearchLogic.h"
#include "UndoLogic.h"
class ParsedDataDeployer
{
private:
	static string error;

public:
	ParsedDataDeployer();
	~ParsedDataDeployer();
	static void executeAdd(ParsedDataPackage addPackage, string fileName);
	static void executeDelete(ParsedDataPackage deletePackage, string fileName, int displayCase);
	static void executeEdit(vector<ParsedDataPackage> editPackages, string fileName, int displayCase);
	static void executeSearch(ParsedDataPackage searchPackage, string fileName);
	static void executeUndo(string fileName);
	static string returnErrorString();
};
#endif