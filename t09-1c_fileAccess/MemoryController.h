#pragma once
#ifndef MEMORY_CONTROLLER
#define MEMORY_CONTROLLER

#include <string>
#include <vector>
#include <iostream>

#endif

using namespace std;

class MemoryController
{
private:
	vector<string> vectorInMemory;

public:
	MemoryController();
	~MemoryController();
	vector<string> getVector();
	void setVector(vector<string> newVector);
	string getLineEntry(int position);
	void appendLineEntry(string lineEntry);
	void insertLineEntry(int position, string line);
	bool deleteLineEntry(int position);
	

};

