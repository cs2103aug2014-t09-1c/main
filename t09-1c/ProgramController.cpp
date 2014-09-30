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



void ProgramController::SendToParser(string input)//placeholder input for scanned input from UI
{
	//if command = add, delete, or edit, use parseAndReturn accordingly

	command = comdAndArgParserObj.getCommand(input); //constructor needed or just static?
	arguments = comdAndArgParserObj.getArguments(input);
	comdAndArgParserObj.commandParser(command, arguments);

	if (command == "add"){
		parseOutput = addParserObj.parseAndReturn(arguments);
	}
	else if (command == "edit"){
		parseOutput = editParserObj.parseAndReturn(arguments);
	}
	else if (command == "delete"){
		parseOutput = deleteParserObj.parseAndReturn(arguments);
	}

}

void ProgramController::SendToLogic(string filename)
{
	if (command == "add"){
		parsDataDeployerObj.executeAdd(parseOutput, filename);
	}
	else if (command == "edit"){
		parsDataDeployerObj.executeEdit(parseOutput, filename);
	}
	else if (command == "delete"){
		parsDataDeployerObj.executeDelete(parseOutput, filename);
	}
}

void ProgramController::ConnectToCommandFeedback(string input)
{

	
}

void ProgramController::ConnectToDoListOutput(string newLineEntry)//input from other logic class a string lineEntry with attributes tags
{
	if (command == "add"){//with condition of = today's date
		fileLogicObj.appendToFile(newLineEntry);
	}
	//else depending on date, use addToPositionNumber method to insert line (SearchLogic to find date?)
	
}
void ProgramController::ConnectToDoListOutput(int position, string newLineEntry)//input from other logic class a string lineEntry with attributes tags
{
	if (command == "edit"){
		fileLogicObj.editLine(position,newLineEntry);
	}
	else if (command == "delete"){
		fileLogicObj.deleteLine(position);
	}
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
