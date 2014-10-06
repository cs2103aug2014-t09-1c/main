#include "stdafx.h"
#include "FileLogic.h"



FileLogic::FileLogic(string fileName) : memoryHandler()
{
	this->fileName = fileName;
	fileAccess();
}


FileLogic::~FileLogic()
{
}

int FileLogic::getSize()
{
	return memoryHandler.getVectorSize();
}

bool FileLogic::fileAccess()
{
	if (FileController::checkFile(fileName))
	{
		memoryHandler.setVector(FileController::parseFileToMemoryVector(fileName));
		vectorSize = memoryHandler.getVectorSize();
		return true;
	}
	else {
		//sendToOutput(FileController::declareFileAccessError);
		return false;
	}
}

string FileLogic::getFileName()
{
	return fileName;
}

void FileLogic::changeFile(string fileName)
{
	if (fileAccess()) {
		this->fileName = fileName;
	}
}

string FileLogic::getLineFromPositionNumber(int position)
{
	if (fileAccess() && position < vectorSize) {
		return memoryHandler.getLineEntry(position);
	}
	else{
		return "";
	}
}

void FileLogic::appendToFile(string lineEntry)
{
	if (fileAccess()) {
		memoryHandler.appendLineEntry(lineEntry);
		FileController::cloneMemoryVectorToFile(fileName, memoryHandler.getVector());
		vectorSize++;
	}
}

void FileLogic::addToPositionNumber(int position, string lineEntry)
{
	if (fileAccess()) {
		if (vectorSize >= position) {
			memoryHandler.insertLineEntry(position, lineEntry);
			FileController::cloneMemoryVectorToFile(fileName, memoryHandler.getVector());
			vectorSize++;
		}
	}
}

void FileLogic::editLine(int position, string lineEntry) 
{
	if (fileAccess()) {
		if (memoryHandler.getVectorSize() > position) {
			memoryHandler.deleteLineEntry(position);
			memoryHandler.insertLineEntry(position, lineEntry);
			FileController::cloneMemoryVectorToFile(fileName, memoryHandler.getVector());
		}
	}
}

void FileLogic::deleteLine(int position)
{
	if (fileAccess()) {
		if (memoryHandler.getVectorSize() > position) {
			memoryHandler.deleteLineEntry(position);
			FileController::cloneMemoryVectorToFile(fileName, memoryHandler.getVector());
			vectorSize = vectorSize -1;
		}
	}
}