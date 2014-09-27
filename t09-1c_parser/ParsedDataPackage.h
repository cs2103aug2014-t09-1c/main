#pragma once
#include "stdafx.h"
#include <string>
#include <list>

using namespace std;

class ParsedDataPackage
{
public:
	ParsedDataPackage();
	~ParsedDataPackage();

	//all data related to event info to be stored are represented here.
	string name;
	int rating;
	string start; //FORMAT SHOULD BE "dd/mm/yyyy HH:MM". NO EXCEPTIONS. MAKE SURE PARSER DOES THIS.
	string end; //FORMAT SHOULD BE "dd/mm/yyyy HH:MM". NO EXCEPTIONS. MAKE SURE PARSER DOES THIS.
	string category;
	string type;




};

