#include "stdafx.h"
#include "FileEntryFormatter.h"


FileEntryFormatter::FileEntryFormatter()
{
}


FileEntryFormatter::~FileEntryFormatter()
{
}

size_t FileEntryFormatter::getAttributedEntryPosition(string attribute, string lineEntry)
{
	string openingAttribute = "<" + attribute + ">";
	size_t foundOpeningAttributeAt = lineEntry.find(openingAttribute);
	size_t attributeEntryStartAt = foundOpeningAttributeAt + attribute.size();
	
	return attributeEntryStartAt;
}

size_t FileEntryFormatter::getAttributeEntrySize(string attribute, string lineEntry)
{
	string closingAttribute = "</" + attribute + ">";
	size_t foundClosingAttributeAt = lineEntry.find(closingAttribute);
	size_t attributeEntrySize = foundClosingAttributeAt - getAttributedEntryPosition(attribute,lineEntry);

	return attributeEntrySize;
}

string FileEntryFormatter::createAttributedEntry(string attribute, string entry)
{
	string openingAttribute = "<" + attribute + ">";
	string closingAttribute = "</" + attribute + ">";
	string attributedEntry = openingAttribute + entry + closingAttribute;

	return attributedEntry;
}

string FileEntryFormatter::getAttributeEntry(string attribute, string lineEntry)
{
	size_t attributeEntryStartAt = getAttributedEntryPosition(attribute, lineEntry);
	size_t attributeEntrySize = getAttributeEntrySize(attribute, lineEntry);
	
	string attributeEntry = lineEntry.substr(attributeEntryStartAt, attributeEntrySize);

	return attributeEntry;
}

string FileEntryFormatter::addAttributedEntryToLineEntry(string attributedEntry, string lineEntry)
{
	lineEntry += attributedEntry;
	return lineEntry;
}

string FileEntryFormatter::deleteAttributedEntryFromLineEntry(string attribute, string lineEntry)
{
	string openingAttribute = "<" + attribute + ">";
	string closingAttribute = "</" + attribute + ">";
	size_t foundOpeningAttributeAt = lineEntry.find(openingAttribute);
	
	size_t attributedEntrySize = openingAttribute.size() + 
		getAttributeEntrySize(attribute, lineEntry) + closingAttribute.size();

	lineEntry.erase(foundOpeningAttributeAt, attributedEntrySize);

	return lineEntry;
}

string FileEntryFormatter::editAttributedEntryFromLineEntry(string attribute, string newAttributeEntry, string lineEntry)
{
	size_t attributeEntryStartAt = getAttributedEntryPosition(attribute, lineEntry);
	size_t attributeEntrySize = getAttributeEntrySize(attribute, lineEntry);

	lineEntry.erase(attributeEntryStartAt, attributeEntrySize);

	lineEntry.insert(attributeEntryStartAt, newAttributeEntry);
}