#pragma once
#ifndef PARSE_DATA_DEPLOYER
#define PARSE_DATA_DEPLOYER

#include "ParsedDataPackage.h"
#include <vector>

class ParsedDataDeployer
{
private:
	static string error;

public:
	ParsedDataDeployer();
	~ParsedDataDeployer();
	static void executeAdd(ParsedDataPackage addPackage, string fileName);
	static void executeDelete(ParsedDataPackage deletePackage, vector<string> keywords, string fileName, int displayCase);
	static void executeEdit(vector<ParsedDataPackage> editPackages, vector<string> keywords, string fileName, int displayCase);
	static vector<string> executeSearch(string searchPackage, string fileName);
	static void executeUndo(string fileName);
	static void executeRedo(string fileName);
	static void executeComplete(ParsedDataPackage completePackage, vector<string> keywords, string fileName, int displayCase);
	static void executeUncomplete(ParsedDataPackage uncompletePackage, vector<string> keywords, string fileName, int displayCase);
	static string returnErrorString();
};
#endif