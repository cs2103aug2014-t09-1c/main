#include "stdafx.h"
#include "FileLogic.h"


FileLogic::FileLogic(string fileName) : memoryHandler()
{
	this->fileName = fileName;
}


FileLogic::~FileLogic()
{
}

int FileLogic::getSize()
{
	return memoryHandler.getVectorSize();
}

bool FileLogic::fileAccess(string fileName)
{
	if (FileController::checkFile(fileName))
	{
		memoryHandler.setVector(FileController::parseFileToMemoryVector(fileName));
		return true;
	}
	else {
		//sendToOutput(FileController::declareFileAccessError);
		return false;
	}
}
void FileLogic::changeFile(string fileName)
{
	if (fileAccess(fileName)) {
		this->fileName = fileName;
	}
}

string FileLogic::getLineFromPositionNumber(int position)
{
	if (fileAccess(fileName)) {
		return memoryHandler.getLineEntry(position);
	}
}

void FileLogic::appendToFile(string lineEntry)
{
	if (fileAccess(fileName)) {
		memoryHandler.appendLineEntry(lineEntry);
		FileController::cloneMemoryVectorToFile(fileName, memoryHandler.getVector());
	}
}

void FileLogic::addToPositionNumber(int position, string lineEntry)
{
	if (fileAccess(fileName)) {
		if (memoryHandler.getVectorSize() > position) {
			memoryHandler.insertLineEntry(position, lineEntry);
			FileController::cloneMemoryVectorToFile(fileName, memoryHandler.getVector());
		}
	}
}

void FileLogic::editLine(int position, string lineEntry) 
{
	if (fileAccess(fileName)) {
		if (memoryHandler.getVectorSize() > position) {
			memoryHandler.deleteLineEntry(position);
			memoryHandler.insertLineEntry(position, lineEntry);
			FileController::cloneMemoryVectorToFile(fileName, memoryHandler.getVector());
		}
	}
}

void FileLogic::deleteLine(int position)
{
	if (fileAccess(fileName)) {
		if (memoryHandler.getVectorSize() > position) {
			memoryHandler.deleteLineEntry(position);
			FileController::cloneMemoryVectorToFile(fileName, memoryHandler.getVector());
		}
	}
}