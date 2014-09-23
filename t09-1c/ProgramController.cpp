#include "stdafx.h"
#include "ProgramController.h"
#include "ParsedDataDeployer.h"


ProgramController::ProgramController()
{
}


ProgramController::~ProgramController()
{
}
void ProgramController::SendToLogic(string parsedString) //readable format
{
	NewLogic::addNewLogic(parsedString);
}
void ProgramController::getOutput(string)
{
	FileOutput::returnOutput();
}