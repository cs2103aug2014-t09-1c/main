#include "stdafx.h"
#include "AddLogic.h"
#include "FileLogic.h"
#include <string>
#include <iostream>


string AddLogic::AddUserInputIntoFile(string userInput, string filename)
{
	FileLogic.addAttributesToFloadEntry(string userInput, string filename);
}


AddLogic::~AddLogic()
{
}


