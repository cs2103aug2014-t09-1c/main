#include "stdafx.h"
#include "AddLogic.h"
#include "FileLogic.h"
#include <string>
#include <iostream>


string AddLogic::AddUserInputIntoFile(string userInput, string filename)
{
	currentLineEntry = floatNewLineEntry(userInput, filename);
	addAttributesToFloatEntry(string userInput, string filename);
}


AddLogic::~AddLogic()
{
}


