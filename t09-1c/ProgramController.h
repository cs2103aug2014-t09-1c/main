#pragma once
#include <string>
#include <sstream>
#include "ParsedDataDeployer.h"
#include "CommandAndArgumentParser.h"
#include "AddParser.h"
#include "ParsedDataPackage.h"
ParsedDataPackage parseOutput;
string command;
string arguments;

class ProgramController
{
public:
	ProgramController();
	~ProgramController();
	void SendToLogic(string parsedString);
	void getOutput(string);
	string SendToParser(string input);
};

