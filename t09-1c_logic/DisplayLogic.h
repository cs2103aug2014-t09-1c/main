#pragma once
#ifndef DISPLAY_LOGIC
#define DISPLAY_LOGIC

#include "BaseClassLogic.h"
#include <iostream>

#define NO_START_STRING \
	"Do by ->"
#define FLOAT_START_STRING \
	"-"
#define FLOAT_END_STRING \
	"-"
#define TODAY \
	"Today, "
#define LAPSED \
	"Lapsed"
#define UNKNOWN \
	"???"
#define STRUCT_PARAM_FORMAT(name, date, time, category) \
	"[" + name + "][" + date + "][" + time + "][" + category + "]"
#define TIME_DELIMETER \
	"-"

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
