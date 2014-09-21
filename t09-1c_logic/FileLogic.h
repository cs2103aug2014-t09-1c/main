#pragma once
#ifndef FILE_LOGIC
#define FILE_LOGIC

#include "FileController.h"
#include "FileEntryFormatter.h"
#include "MemoryController.h"

#endif

class FileLogic
{
private:
	string fileName;
	MemoryController memoryHandler;
	
	string currentLineEntry;
	int currentPosition;

public:
	FileLogic(string fileName);
	~FileLogic();

	void fileAccess(string fileName);
	void changeFile(string fileName);

	string getCurrentLineEntry();
	int getCurrrentPosition();

	//These are floating file logic functions that will be committed.
	void floatNewLineEntry(string firstAttribute, string firstAttributeEntry);
	void addAttributesToFloatEntry(string attribute, string attributeEntry);
	void editAttributedInFloatEntry(string attribute, string newAttributeEntry);
	void deleteAttributedFromFloatEntry(string attribute);
	void initialiseFloatEntry();
	
	//These are floating file logic functions that accesses IO functions
	void goToPositionNumber(int position);
	void commitAdd();
	void commitEdit();
	void commitDelete();
};

