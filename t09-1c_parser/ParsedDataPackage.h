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
	string rating; // 1, 2 or 3 in string format
	string start; //FORMAT SHOULD BE "dd/mm/yyyy HH:MM". NO EXCEPTIONS. MAKE SURE PARSER DOES THIS.
	string end; //FORMAT SHOULD BE "dd/mm/yyyy HH:MM". NO EXCEPTIONS. MAKE SURE PARSER DOES THIS.
	string category; // Empty string for uncategorised
	string type; // "timed", "deadline" or "open" (no deadline specified)




};

