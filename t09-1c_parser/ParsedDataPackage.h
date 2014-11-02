#pragma once
#ifndef PARSED_DATA_PACKAGE
#define PARSED_DATA_PACKAGE

#include "stdafx.h"
#include <string>
#include <map>
#include <vector>
#include "assert.h"


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

	

	//all data related to event info to be stored are represented here.
	string name; //event name
	string date; //date should be in dd/mm/yyyy or empty string. NO EXCEPTIONS. MAKE SURE PARSER DOES THIS.
	string start; //FORMAT SHOULD BE "HH:MM" or empty string. NO EXCEPTIONS. MAKE SURE PARSER DOES THIS.
	string end; //FORMAT SHOULD BE "HH:MM" or empty string. NO EXCEPTIONS. MAKE SURE PARSER DOES THIS.
	string category; // Empty string for uncategorised
	int lineNum; //line to delete or edit
};
#endif

