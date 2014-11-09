#pragma once
#ifndef FILE_ENTRY_FORMATTER
#define FILE_ENTRY_FORMATTER

#include <string>
#include <iostream>

#define OPENING_ATTR(attribute) \
	"<" + attribute + ">"
#define CLOSING_ATTR(attribute) \
	"</" + attribute + ">"

using namespace std;

class FileEntryFormatter
{

private:
	static size_t getAttributedEntryPosition(string attribute, string lineEntry);
	static size_t getAttributeEntrySize(string attribute, string lineEntry);

public:
	FileEntryFormatter();
	~FileEntryFormatter();

	//Methods below deal with entry formatting.
	/*
	*Encloses given entry to the given attribute
	*Returns a string containing the attributed entry
	*/
	static string createAttributedEntry(string attribute, string entry);
	/*
	*Gets entry of the given attribute found in lineEntry
	*Returns a string containing the entry. If no attribute matching
	*string attribute is found, return empty string.
	*/
	static string getAttributeEntry(string attribute, string lineEntry);
	/*
	*Appends attributed entry to lineEntry
	*Returns the line with the attributed entry appended
	*/
	static string addAttributedEntryToLineEntry(string attributedEntry, string lineEntry);
	/*
	*Deletes attributed entry to lineEntry
	*Returns the line with the attributed entry deleted
	*/
	static string deleteAttributedEntryFromLineEntry(string attribute, string lineEntry);
	/*
	*Edits attributed entry in lineEntry to that of newAttributeEntry
	*Returns the line with the attributed entry edited
	*/
	static string editAttributedEntryFromLineEntry(string attribute, string newAttributeEntry, string lineEntry);
};

#endif