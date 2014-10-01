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

	bool fileAccess();
	void changeFile(string fileName);
	
	//These are floating file logic functions that accesses IO functions
	int getSize();
	string getLineFromPositionNumber(int position);
	void appendToFile(string lineEntry);
	void addToPositionNumber(int position, string lineEntry);
	void editLine(int position, string newLineEntry);
	void deleteLine(int position);
};

#endif

