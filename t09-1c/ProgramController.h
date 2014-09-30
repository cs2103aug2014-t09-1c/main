#pragma once
#include <string>
#include <sstream>
#include "ParsedDataDeployer.h"
#include "CommandAndArgumentParser.h"
#include "AddParser.h"
#include "ParsedDataPackage.h"
#include "FileLogic.h"



class ProgramController
{
private:
	ParsedDataPackage parseOutput;
	string command;
	string arguments;
	AddParser addParserObj;
	DeleteParser deleteParserObj;
	EditParser editParserObj;
	CommandAndArgumentParser comdAndArgParserObj;
	ParsedDataDeployer parsDataDeployerObj;
	FileLogic fileLogicObj;
public:
	ProgramController();
	~ProgramController();
	void SendToLogic(string parsedString);
	void getOutput(string);
	void SendToParser(string input);
	void ConnectToCommandFeedback(string input);
	void ConnectToDoListOutput(string newLineEntry);
	void ConnectToDoListOutput(int position, string newLineEntry);
};

