#pragma once
#ifndef PROGRAM_CONTROLLER
#define PROGRAM_CONTROLLER

#include <string>
#include <sstream>
#include "ParsedDataDeployer.h"
#include "CommandAndArgumentParser.h"
#include "AddParser.h"
#include "ParsedDataPackage.h"
#include "FileLogic.h"

#define FILENAME \
	"example.txt"


class ProgramController
{
private:
	FileLogic fileLogicObj;

public:
	ProgramController(string filename);
	~ProgramController();
	void getOutput(string);
	void executeEntry(string input);
	void ConnectToCommandFeedback(string input);
	void ConnectToDoListOutput(string newLineEntry);
	void ConnectToDoListOutput(int position, string newLineEntry);
};

#endif
