//@author A0116410Y
#include "stdafx.h"
#include "FileLogic.h"

FileLogic::FileLogic(string fileName) : memoryHandler()
{
	this->fileName = fileName;
	try {
		fileAccess();
	}
	catch (const exception& ex) {
		throw runtime_error(ex.what());
	}
}

FileLogic::FileLogic(vector<string> testVector) : memoryHandler()
{
	memoryHandler.setVector(testVector);
	isTestMode = true;
}

FileLogic::~FileLogic()
{
}

int FileLogic::getSize()
{
	return memoryHandler.getVectorSize();
}

vector<string> FileLogic::getVector()
{
	return memoryHandler.getVector();
}

void FileLogic::fileAccess()
{
	if (FileController::checkFile(fileName))
	{
		memoryHandler.setVector(FileController::parseFileToMemoryVector(fileName));
	}
	else {
		throw runtime_error(FILE_ACCESS_ERROR);
	}
}

string FileLogic::getFileName()
{
	return fileName;
}

void FileLogic::changeFile(string fileName)
{
	this->fileName = fileName;
	try {
		fileAccess();
	}
	catch (const exception& ex) {
		throw runtime_error(ex.what());
	}
}

string FileLogic::getLineFromPositionNumber(int position)
{
	if (position < getSize()) {
		return memoryHandler.getLineEntry(position);
	}
	else {
		return "";
	}
}

void FileLogic::appendToFile(string lineEntry)
{
	memoryHandler.appendLineEntry(lineEntry);
	if (!isTestMode) {
		FileController::cloneMemoryVectorToFile(fileName, memoryHandler.getVector());
	}
}

void FileLogic::addToPositionNumber(int position, string lineEntry)
{
	if (getSize() >= position) {
		memoryHandler.insertLineEntry(position, lineEntry);
		if (!isTestMode) {
			FileController::cloneMemoryVectorToFile(fileName, memoryHandler.getVector());
		}
	}
}

void FileLogic::editLine(int position, string lineEntry) 
{
	if (memoryHandler.getVectorSize() > position) {
		memoryHandler.deleteLineEntry(position);
		memoryHandler.insertLineEntry(position, lineEntry);
		if (!isTestMode) {
			FileController::cloneMemoryVectorToFile(fileName, memoryHandler.getVector());
		}
	}
}

void FileLogic::deleteLine(int position)
{
	if (memoryHandler.getVectorSize() > position) {
		memoryHandler.deleteLineEntry(position);
		if (!isTestMode) {
			FileController::cloneMemoryVectorToFile(fileName, memoryHandler.getVector());
		}
	}
}

string FileLogic::createAttributedEntry(string attribute, string entry)
{
	return FileEntryFormatter::createAttributedEntry(attribute, entry);
}

string FileLogic::getAttributeEntry(string attribute, string lineEntry)
{
	return FileEntryFormatter::getAttributeEntry(attribute, lineEntry);
}

string FileLogic::addAttributedEntryToLineEntry(string attributedEntry, string lineEntry)
{
	return FileEntryFormatter::addAttributedEntryToLineEntry(attributedEntry, lineEntry);
}

string FileLogic::deleteAttributedEntryFromLineEntry(string attribute, string lineEntry)
{
	return FileEntryFormatter::deleteAttributedEntryFromLineEntry(attribute, lineEntry);
}

string FileLogic::editAttributedEntryFromLineEntry(string attribute, string newAttributeEntry, string lineEntry)
{
	return FileEntryFormatter::editAttributedEntryFromLineEntry(attribute, newAttributeEntry, lineEntry);
}