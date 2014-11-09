#include "stdafx.h"
#include "ParsedDataPackage.h"

ParsedDataPackage::ParsedDataPackage()
{
}

ParsedDataPackage::~ParsedDataPackage()
{
}

map<string, string> ParsedDataPackage::getLineEntries()
{
	return lineEntries;
}

map<string, int> ParsedDataPackage::getStartEndPositions()
{
	return startEndPositions;
}

void ParsedDataPackage::insertAttribute(string attribute, string entry)
{
	if (isDuplicate(attribute)) {
		assert(false && "PARSED DATA PACKAGE SHOULD NOT HAVE DUPLICATE ATTRIBUTES");
	}

	lineEntries.insert(pair<string, string>(attribute, entry));
	insertedAttributes.push_back(attribute);
}

void ParsedDataPackage::insertAttribute(string attribute, int entry)
{
	if (isDuplicate(attribute)) {
		assert(false && "PARSED DATA PACKAGE SHOULD NOT HAVE DUPLICATE ATTRIBUTES");
	}

	startEndPositions.insert(pair<string, int>(attribute, entry));
	insertedAttributes.push_back(attribute);
}

bool ParsedDataPackage::isDuplicate(string attribute)
{
	bool duplicate = false;
	int size = insertedAttributes.size();

	for (int i = 0; i < size; ++i) {
		if (insertedAttributes[i] == attribute) {
			duplicate = true;
			break;
		}
	}

	return duplicate;
}