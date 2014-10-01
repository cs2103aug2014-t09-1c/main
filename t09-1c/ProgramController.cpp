#include "stdafx.h"
#include "ProgramController.h"
#include "ParsedDataDeployer.h"
#include "ParsedDataPackage.h"
#include <vector>

//after an input is scanned by UI method, call to method sendToParse is made to send input to Parser
//after Parser returns the variables in ParsedDataPackage, send the details to logic
//after file output returns an output, controller sends it to UI

ProgramController::ProgramController(string fileName) : fileLogicObj(FILENAME)
{
}


ProgramController::~ProgramController()
{
}



void ProgramController::executeEntry(string input)//placeholder input for scanned input from UI
{
	//if command = add, delete, or edit, use parseAndReturn accordingly

	CommandAndArgumentParser inputParse(input);
	string command = inputParse.command;
	string arguments = inputParse.arguments;

	if (command == "add") {
		AddParser addParsing;
		ParsedDataPackage addPackage = addParsing.parseAndReturn(arguments);
		ParsedDataDeployer::executeAdd(addPackage, fileLogicObj);
	}
	else if (command == "edit"){
		EditParser editParsing;
		vector<ParsedDataPackage> editPackages = editParsing.parseAndReturn(arguments);
		ParsedDataDeployer::executeEdit(editPackages, fileLogicObj);
	}
	else if (command == "delete"){
		DeleteParser deleteParsing;
		ParsedDataPackage deletePackage = deleteParsing.parseAndReturn(arguments);
		ParsedDataDeployer::executeDelete(deletePackage, fileLogicObj);
	}

}

void ProgramController::ConnectToCommandFeedback(string input)
{

	
}

void ProgramController::ConnectToDoListOutput(string newLineEntry)//input from other logic class a string lineEntry with attributes tags
{
	
	//else depending on date, use addToPositionNumber method to insert line (SearchLogic to find date?)
	
}
void ProgramController::ConnectToDoListOutput(int position, string newLineEntry)//input from other logic class a string lineEntry with attributes tags
{
	//else return error


}
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
