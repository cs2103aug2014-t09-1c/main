#include "stdafx.h"
#include "FileController.h"


FileController::FileController()
{
}


FileController::~FileController()
{
}

bool FileController::checkFile(string fileName)
{
	ofstream myFile(fileName, ios::out | ios::app);

	if (myFile.is_open()) {
		myFile << "";
		myFile.close();
		return true;
	}
	else { return false; }
}

vector<string> FileController::parseFileToMemoryVector(string fileName)
{
	vector<string> toMemory;
	string line;

	ifstream myFile(fileName);

	if (myFile.is_open()) {
		while (getline(myFile, line)) {
			toMemory.push_back(line);
		}
		myFile.close();
	}
	else { return toMemory; }

	return toMemory;
}
bool FileController::cloneMemoryVectorToFile(string fileName, vector<string> memVector)
{
	std::ofstream myFile(fileName); 
	for (vector<string>::iterator it = memVector.begin(); it != memVector.end(); ++it) {
		myFile << *it << "\n"; 
	} 
	myFile.close();
}

string FileController::declareFileAccessError()
{
	return BAD_ACCESS;
}