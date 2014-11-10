//@author A0116410Y
#pragma once
#ifndef MEMORY_CONTROLLER
#define MEMORY_CONTROLLER

#include <string>
#include <vector>
#include <iostream>



using namespace std;

class MemoryController
{
private:
	vector<string> vectorInMemory;

public:
	MemoryController();
	~MemoryController();
	vector<string> getVector();
	int getVectorSize();
	void setVector(vector<string> newVector);
	string getLineEntry(int position);
	void appendLineEntry(string lineEntry);
	void insertLineEntry(int position, string line);
	bool deleteLineEntry(int position);
	

};

#endif

