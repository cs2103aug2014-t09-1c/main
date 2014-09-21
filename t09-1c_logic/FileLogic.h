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
	//Example: currentLineEntry = "<firstAttribute>firstAttributeEntry</firstAttribute>"
	void addAttributesToFloatEntry(string attribute, string attributeEntry);
	//Example: currentLineEntry = "<firstAttribute>firstAttributeEntry</firstAttribute><attribute>attributeEntry</attribute>
	void editAttributedInFloatEntry(string attribute, string newAttributeEntry);
	//Example:: from "<firstAttribute>firstAttributeEntry</firstAttribute><attribute>attributeEntry</attribute>"
	//to "<firstAttribute>firstAttributeEntry</firstAttribute><attribute>newAttributeEntry</attribute>"
	void deleteAttributedFromFloatEntry(string attribute);
	//Example:: from "<firstAttribute>firstAttributeEntry</firstAttribute><attribute>attributeEntry</attribute>"
	//to "<firstAttribute>firstAttributeEntry</firstAttribute>"
	string getAttributeFromFloatEntry(string attribute);
	//Example:: from "<firstAttribute>firstAttributeEntry</firstAttribute><attribute>attributeEntry</attribute>"
	//get back string "attributeEntry"
	void initialiseFloatEntry();
	
	//These are floating file logic functions that accesses IO functions
	void goToPositionNumber(int position);
	void commitAdd();
	void commitEdit();
	void commitDelete();
};

