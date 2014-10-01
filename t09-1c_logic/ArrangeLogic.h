#pragma once
#ifndef ARRANGE_LOGIC
#define ARRANGE_LOGIC

#include <iostream>
#include <vector>
#include "FileLogic.h"

using namespace std;

class ArrangeLogic
{
private:
	FileLogic fileHandler;

public:
	ArrangeLogic(FileLogic fileHandler);
	~ArrangeLogic();

	pair<vector<string>, vector<int>> getListOfDate(string date);
};

#endif

