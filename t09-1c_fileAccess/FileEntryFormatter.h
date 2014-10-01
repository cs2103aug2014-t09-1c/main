#pragma once
#ifndef FILE_ENTRY_FORMATTER
#define FILE_ENTRY_FORMATTER

#include <string>
#include <iostream>



using namespace std;

class FileEntryFormatter
{
public:
	FileEntryFormatter();
	~FileEntryFormatter();

	//These methods are class exclusive helper functions.
	static size_t getAttributedEntryPosition(string attribute, string lineEntry);
	static size_t getAttributeEntrySize(string attribute, string lineEntry);

	//Methods below deal with entry formatting.
	static string createAttributedEntry(string attribute, string entry);
	static string getAttributeEntry(string attribute, string lineEntry);
	static string addAttributedEntryToLineEntry(string attributedEntry, string lineEntry);
	static string deleteAttributedEntryFromLineEntry(string attribute, string lineEntry);
	static string editAttributedEntryFromLineEntry(string attribute, string newAttributeEntry, string lineEntry);
};

#endif