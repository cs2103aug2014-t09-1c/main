#pragma once
#ifndef ARRANGE_LOGIC
#define ARRANGE_LOGIC

#include <iostream>
#include <vector>

using namespace std;

class ArrangeLogic
{
private:
	FileLogic fileHandler;
public:
	ArrangeLogic(string fileName);
	~ArrangeLogic();

	pair<vector<string>, vector<int>> getListOfDate(string date);
};

#endif

