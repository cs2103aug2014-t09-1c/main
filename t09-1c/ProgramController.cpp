#include "stdafx.h"
#include "ProgramController.h"
#include "ParsedDataDeployer.h"
#include "ParsedDataPackage.h"
#include <vector>

//after an input is scanned by UI method, call to method sendToParse is made to send input to Parser
//after Parser returns the variables in ParsedDataPackage, send the details to logic
//after file output returns an output, controller sends it to UI

ProgramController::ProgramController(string fileName)
{
	this->fileName = fileName;
}


ProgramController::~ProgramController()
{
}


void ProgramController::executeEntry(string input)//placeholder input for scanned input from UI
{
	//if command = add, delete, or edit, use parseAndReturn accordingly

	CommandAndArgumentParser inputParse(input);
	command = inputParse.command;
	arguments = inputParse.arguments;

	if (command == "add") {
		AddParser addParsing;
		dataPackage = addParsing.parseAndReturn(arguments);
		ParsedDataDeployer::executeAdd(dataPackage, fileName);
	}
	else if (command == "edit"){
		EditParser editParsing;
		dataPackages = editParsing.parseAndReturn(arguments);
		ParsedDataDeployer::executeEdit(dataPackages, fileName);
	}
	else if (command == "delete"){
		DeleteParser deleteParsing;
		dataPackage = deleteParsing.parseAndReturn(arguments);
		ParsedDataDeployer::executeDelete(dataPackage, fileName);
	}

}

void ProgramController::ConnectToCommandFeedback(string input)
{

	
}

void ProgramController::ConnectToDoListOutput(vector<string> vectorOutput)//input from other logic class a string lineEntry with attributes tags
{
	//send to UI e.g. >>> vectorOutput.parseFileToMemoryVector(FILENAME);
	
	
}



/*void ProgramController::ConnectToDoListOutput(int position, string newLineEntry)//input from other logic class a string lineEntry with attributes tags
{
	if (command == "add"){
		
	}
	//else return error
	int position = dataPackage.lineNum;
	
}*/
/*void ProgramController::SendToLogic() //now that deployer does this instead
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
	
}*/
/*void ProgramController::getOutput(string)//now that logic does this instead.
{
	FileOutput::returnOutput();
}*/
