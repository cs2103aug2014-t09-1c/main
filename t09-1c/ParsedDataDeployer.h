#pragma once
#ifndef PARSE_DATA_DEPLOYER
#define PARSE_DATA_DEPLOYER

#include "ParsedDataPackage.h"

class ParsedDataDeployer
{
private:
	static string error;
	string fileName;

public:
	ParsedDataDeployer(string fileName);
	~ParsedDataDeployer();
	void executeAdd(ParsedDataPackage addPackage);
	void executeDelete(ParsedDataPackage deletePackage, string date, vector<string> keywords, int displayCase);
	void executeEdit(ParsedDataPackage editPackage, string date, vector<string> keywords, int displayCase);
	vector<string> executeSearch(string fileName);
	void executeUndo();
	void executeRedo();
	void executeComplete(ParsedDataPackage completePackage, string date, vector<string> keywords, int displayCase);
	void executeUncomplete(ParsedDataPackage uncompletePackage, string date, vector<string> keywords, int displayCase);
	string returnErrorString();
};
#endif