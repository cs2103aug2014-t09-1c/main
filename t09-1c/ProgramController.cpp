#include "stdafx.h"
#include "ProgramController.h"
#include "ParsedDataDeployer.h"

//after an input is scanned by UI method, call to method sendToParse is made to send input to Parser
//after Parser returns the variables in ParsedDataPackage, send the details to logic
//after file output returns an output, controller sends it to UI

ProgramController::ProgramController()
{
}


ProgramController::~ProgramController()
{
}



string ProgramController::SendToParser(string input)//placeholder input for scanned input from UI
{
	//if command = add, delete, or edit, use parseAndReturn accordingly
	command = CommandAndArgumentParser::getCommand(input); //constructor needed or just static?
	arguments = CommandAndArgumentParser::getArguments(input);
	CommandAndArgumentParser::commandParser(command, arguments);

	if (command == "add"){
		parseOutput = AddParser::parseAndReturn(string arguments);
	}
	else if (command == "edit"){
		parseOutput = EditParser::parseAndReturn(string arguments);
	}
	else if (command == "delete"){
		parseOutput = DeleteParser::parseAndReturn(string arguments);
	}
}
void ProgramController::SendToLogic() 
{
	if (command == "add"){	
		BaseClassLogic::addParsedOutput(parseOutput);
	}
	else if (command == "edit"){
		BaseClassLogic::editParsedOutput(parseOutput);
	}
	else if (command == "delete"){
		BaseClassLogic::deleteParsedOutput(parseOutput);
	}
	
}
void ProgramController::getOutput(string)
{
	FileOutput::returnOutput();
}
