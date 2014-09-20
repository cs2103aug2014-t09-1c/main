#pragma once
#include "stdafx.h"
#include <string>

using namespace std;

class ParsedDataPackage
{
protected:
	string event;
	int priority;
	
public:
	ParsedDataPackage();
	~ParsedDataPackage();
};

