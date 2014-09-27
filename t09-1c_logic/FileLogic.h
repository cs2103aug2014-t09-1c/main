#pragma once
#ifndef FILE_LOGIC
#define FILE_LOGIC

#include "FileController.h"
#include "MemoryController.h"


class FileLogic
{
private:
	string fileName;
	MemoryController memoryHandler;

public:
	FileLogic(string fileName);
	~FileLogic();

	bool fileAccess(string fileName);
	void changeFile(string fileName);
	
	//These are floating file logic functions that accesses IO functions
	string getLineFromPositionNumber(int position);
	void appendToFile(string lineEntry);
	void addToPositionNumber(int position, string lineEntry);
	void editLine(int position, string newLineEntry);
	void deleteLine(int position);
};

#endif

