#include "stdafx.h"
#include "MemoryController.h"


MemoryController::MemoryController()
{
}


MemoryController::~MemoryController()
{
}

vector<string> MemoryController::getVector()
{
	return vectorInMemory;
}

void MemoryController::setVector(vector<string> newVector)
{
	vectorInMemory = newVector;
}

string MemoryController::getLineEntry(int position)
{
	return vectorInMemory[position];
}

void MemoryController::appendLineEntry(string lineEntry)
{
	vectorInMemory.push_back(lineEntry);
}

void MemoryController::insertLineEntry(int position, string line)
{
	vector<string>::iterator it;
	it = vectorInMemory.begin() + position;
	vectorInMemory.insert(it, line);
}

bool MemoryController::deleteLineEntry(int position)
{
	if (position < vectorInMemory.size()) {
		vectorInMemory.erase(vectorInMemory.begin() + position);
		return true;
	}
	else { return false; }
}

