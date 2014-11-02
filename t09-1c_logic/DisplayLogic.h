#pragma once
#ifndef DISPLAY_LOGIC
#define DISPLAY_LOGIC

#include "BaseClassLogic.h"
#include <iostream>

#define NO_START_STRING \
	"In Progress"
#define FLOAT_START_STRING \
	"To Infinity"
#define FLOAT_END_STRING \
	"And Beyond"
#define TODAY \
	"Today, "
#define LAPSED \
	"Lapsed"

using namespace std;

class DisplayLogic
	: public BaseClassLogic
{
private:
	vector<string> putToVectorEventDatails(string line);

public:
	DisplayLogic(string fileName, string date, vector<string> keywords, int displayCase);
	DisplayLogic(vector<string> testVector, string date, vector<string> keywords, int displayCase);
	~DisplayLogic();

	vector<vector<string>> displayEvents();
	string formatContentsToLineEdit(int position);
	
};

#endif 
