#pragma once
#ifndef PARSED_DATA_PACKAGE
#define PARSED_DATA_PACKAGE

#include "stdafx.h"
#include <string>
#include <map>
#include <vector>
#include "assert.h"

// All data related to event info to be stored are represented here.
// Event name
// Date should be in dd/mm/yyyy or empty string. NO EXCEPTIONS. MAKE SURE PARSER DOES THIS.
// FORMAT SHOULD BE "HH:MM" or empty string. NO EXCEPTIONS. MAKE SURE PARSER DOES THIS.
// FORMAT SHOULD BE "HH:MM" or empty string. NO EXCEPTIONS. MAKE SURE PARSER DOES THIS.
// Empty string for uncategorised
// Line to delete or edit

using namespace std;

class ParsedDataPackage
{
private:
	map<string, string> lineEntries;
	map<string, int> startEndPositions;

	bool isDuplicate(string attribute);
	vector<string> insertedAttributes;

public:
	ParsedDataPackage();
	~ParsedDataPackage();

	map<string, string> getLineEntries();
	map<string, int> getStartEndPositions();
	void insertAttribute(string attribute, string entry);
	void insertAttribute(string attribute, int entry);

};
#endif
