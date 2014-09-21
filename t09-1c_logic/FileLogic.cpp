#include "stdafx.h"
#include "FileLogic.h"


FileLogic::FileLogic(string fileName) : memoryHandler()
{
	this->fileName = fileName;
}


FileLogic::~FileLogic()
{
}

void FileLogic::fileAccess(string fileName)
{
	if (FileController::checkFile(fileName))
	{
		memoryHandler.setVector(FileController::parseFileToMemoryVector(fileName));
	}
	else {
		//sendToOutput(FileController::declareFileAccessError);
	}
}
void FileLogic::changeFile(string fileName)
{
	this->fileName = fileName;
	fileAccess(fileName);
}

string FileLogic::getCurrentLineEntry()
{
	return currentLineEntry;
}

int FileLogic::getCurrrentPosition()
{
	return currentPosition;
}

void FileLogic::initialiseFloatEntry()
{
	currentLineEntry.clear();
	currentPosition = -1;
}

//These are floating file logic functions that will be committed.
void FileLogic::floatNewLineEntry(string firstAttribute, string firstAttributeEntry)
{
	initialiseFloatEntry();

	addAttributesToFloatEntry(firstAttribute, firstAttributeEntry);
}

void FileLogic::addAttributesToFloatEntry(string attribute, string attributeEntry)
{
	string attributedEntry = FileEntryFormatter::createAttributedEntry(attribute, attributedEntry);
	FileEntryFormatter::addAttributedEntryToLineEntry(attributedEntry, currentLineEntry);
}

void FileLogic::editAttributedInFloatEntry(string attribute, string newAttributeEntry)
{
	FileEntryFormatter::editAttributedEntryFromLineEntry(attribute, newAttributeEntry, currentLineEntry);
}

void FileLogic::deleteAttributedFromFloatEntry(string attribute)
{
	FileEntryFormatter::deleteAttributedEntryFromLineEntry(attribute, currentLineEntry);
}

string FileLogic::getAttributeFromFloatEntry(string attribute)
{
	return FileEntryFormatter::getAttributeEntry(attribute, currentLineEntry);
}

//These are floating file logic functions that accesses IO functions
void FileLogic::goToPositionNumber(int position)
{
	currentLineEntry = memoryHandler.getLineEntry(position);
	currentPosition = position;
}

void FileLogic::commitAdd()
{
	memoryHandler.appendLineEntry(getCurrentLineEntry());
	FileController::cloneMemoryVectorToFile(fileName, memoryHandler.getVector());
	initialiseFloatEntry();
}

void FileLogic::commitEdit() 
{
	if (getCurrrentPosition() > -1) {
		memoryHandler.deleteLineEntry(getCurrrentPosition());
		memoryHandler.insertLineEntry(getCurrrentPosition(), currentLineEntry);
		FileController::cloneMemoryVectorToFile(fileName, memoryHandler.getVector());
		initialiseFloatEntry();
	}
}

void FileLogic::commitDelete()
{
	if (getCurrrentPosition() > -1) {
		memoryHandler.deleteLineEntry(getCurrrentPosition());
		FileController::cloneMemoryVectorToFile(fileName, memoryHandler.getVector());
		initialiseFloatEntry();
	}
}