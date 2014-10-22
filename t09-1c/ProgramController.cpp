#include "stdafx.h"
#include "ProgramController.h"
#include "ParsedDataDeployer.h"
#include "ParsedDataPackage.h"
#include <vector>
#include "DisplayLogic.h"
#include "TimeParser.h"
#include <stdio.h>      //
#include <assert.h>//

//after an input is scanned by UI method, call to method sendToParse is made to send input to Parser
//after Parser returns the variables in ParsedDataPackage, send the details to logic
//after file output returns an output, controller sends it to UI

ProgramController::ProgramController(string fileName)
{
	this->fileName = fileName;
	displayDate = TimeParser::parseDayOfWeek("today");
}


ProgramController::~ProgramController()
{
}


void ProgramController::executeEntry(string input)//placeholder input for scanned input from UI
{
	CommandAndArgumentParser inputParse(input);

	command = inputParse.command;
	arguments = inputParse.arguments;

	if (command == "add") {
		AddParser addParsing;
		dataPackage = addParsing.parseAndReturn(arguments);
		if (addParsing.isInputValid())
		{
			errorString = addParsing.getErrorString();
		}
		else
		{
			ParsedDataDeployer::executeAdd(dataPackage, fileName);
		}
		
	}
	else if (command == "edit"){
		EditParser editParsing;
		dataPackages = editParsing.parseAndReturn(arguments);
		if (dataPackages[0].date.empty()) {
			ParsedDataPackage deletePack = dataPackages[0];
			deletePack.date = displayDate;
			dataPackages[0] = deletePack;
			ParsedDataDeployer::executeEdit(dataPackages, fileName, displayCase);
		}
		else {
			ParsedDataDeployer::executeEdit(dataPackages, fileName, 2);
		}
	}
	else if (command == "delete"){
		DeleteParser deleteParsing;
		dataPackage = deleteParsing.parseAndReturn(arguments);
		if (deleteParsing.isInputValid())
		{
			errorString = deleteParsing.getErrorString();
		}
		else if (dataPackage.date.empty()) {
			dataPackage.date = displayDate;
			ParsedDataDeployer::executeDelete(dataPackage, fileName, displayCase);
		}
		else {
			ParsedDataDeployer::executeDelete(dataPackage, fileName, 2);
		}
	}
	else if (command == "search"){
		SearchParser searchParsing;
		dataPackage = searchParsing.parseAndReturn(arguments);
		if (searchParsing.isInputValid())
		{
			errorString = searchParsing.getErrorString();
		}
		//else ParsedDataDeployer::executeSearch(dataPackage, fileName);  -> waiting for search logic
	}
	else if (command == "undo"){
		ParsedDataDeployer::executeUndo(fileName);
	}

}

vector<vector<string>> ProgramController::refreshTableDisplay()
{
	return displayTable(displayDate);
}

vector<vector<string>> ProgramController::displayTable(string date)
{
	vector<vector<string>> forTableDisplay;
	DisplayLogic displayer(fileName);
	if (displayCase == 0) {
		forTableDisplay = displayer.collectEventsFromDate(date);
	}
	else {
		forTableDisplay = displayer.collectEventsOnDate(date);
	}
	return forTableDisplay;
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
