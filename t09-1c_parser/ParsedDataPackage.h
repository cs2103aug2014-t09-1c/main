#pragma once
#include "stdafx.h"
#include <string>

using namespace std;

class ParsedDataPackage
{
public:
	ParsedDataPackage();
	~ParsedDataPackage();

	//all data related to event info to be stored are represented here.
	string name; //event name
	string date; //date should be in dd/mm/yyyy or empty string. NO EXCEPTIONS. MAKE SURE PARSER DOES THIS.
	string start; //FORMAT SHOULD BE "HH:MM" or empty string. NO EXCEPTIONS. MAKE SURE PARSER DOES THIS.
	string end; //FORMAT SHOULD BE "HH:MM" or empty string. NO EXCEPTIONS. MAKE SURE PARSER DOES THIS.
	string category; // Empty string for uncategorised
	string lineNum; //line to delete or edit
};

