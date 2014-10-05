#pragma once
#include "BaseClassLogic.h"
#include <string>
#include <iostream>


class SearchLogic :
	public BaseClassLogic
{

private:

	FileLogic fileHandler;


public:
	
	SearchLogic(FileLogic fileHandler);
	~SearchLogic();

	string searchEntryDate(string date);
	string searchEntry(string userEntry);
	string searchForLineInFile(string userEntry);

};

