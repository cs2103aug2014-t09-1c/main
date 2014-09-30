#pragma once
#ifndef UI_OUTPUT
#define UI_OUTPUT

#include <vector>
#include <iostream>

using namespace std;

class UiOutput
{
public:
	UiOutput();
	~UiOutput();

	void sendToTableOutput(vector<vector<string>> data);
	// Table display includes name, date, start, end, category and complete?
	void sendToSuggestionOutput(vector<string> display, vector<string> command);
	// sends to suggestion output display strings and its resulting command when the display
	// string is clicked. 
	
};

#endif