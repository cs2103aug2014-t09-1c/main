//@author A0116410Y
#pragma once
#ifndef FILE_CONTROLLER
#define FILE_CONTROLLER

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#define BAD_ACCESS \
	"Error. File cannot be accessed."

using namespace std;

class FileController
{
protected:
	FileController();
	~FileController();

public:
	//Checks if file is open.
	static bool checkFile(string fileName);
	//Copies file contents to memory in a vector.
	static vector<string> parseFileToMemoryVector(string fileName);
	//Re-writes file as copy of the vector input.
	static bool cloneMemoryVectorToFile(string fileName, vector<string> memVector);
	static string declareFileAccessError();
};

#endif
