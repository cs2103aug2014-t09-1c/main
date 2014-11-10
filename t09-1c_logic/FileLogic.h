//@author A0116410Y
#pragma once
#ifndef FILE_LOGIC
#define FILE_LOGIC

#include "FileEntryFormatter.h"
#include "FileController.h"
#include "MemoryController.h"

#define FILE_ACCESS_ERROR \
	"File cannot be accessed"

class FileLogic
{
private:
	
	string fileName;
	MemoryController memoryHandler;

	bool isTestMode = false;

public:

	FileLogic(string fileName);
	FileLogic(vector<string> testVector);
	~FileLogic();

	void fileAccess();
	void changeFile(string fileName);
	string getFileName();
	
	//These are floating file logic functions that accesses IO functions
	int getSize();
	vector<string> getVector();
	string getLineFromPositionNumber(int position);
	void appendToFile(string lineEntry);
	void addToPositionNumber(int position, string lineEntry);
	void editLine(int position, string newLineEntry);
	void deleteLine(int position);

	/*These are the interface methods for the FileEntryFormatter class.
	  Consult FileEntryFormatter.h for more information about these methods. */
	static string createAttributedEntry(string attribute, string entry);
	static string getAttributeEntry(string attribute, string lineEntry);
	static string addAttributedEntryToLineEntry(string attributedEntry, string lineEntry);
	static string deleteAttributedEntryFromLineEntry(string attribute, string lineEntry);
	static string editAttributedEntryFromLineEntry(string attribute, string newAttributeEntry, string lineEntry);
};

#endif

