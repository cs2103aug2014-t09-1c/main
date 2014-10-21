#include "stdafx.h"
#include "BaseClassLogic.h"


BaseClassLogic::BaseClassLogic()
{
}


BaseClassLogic::~BaseClassLogic()
{
}

void BaseClassLogic::toLog(string log)
{
	FileLogic logger("log.txt");
	logger.appendToFile(log);
}
