#pragma once
#ifndef BASE_CLASS_LOGIC
#define BASE_CLASS_LOGIC

#include "FileLogic.h"

class BaseClassLogic
{
protected:
	BaseClassLogic();
	~BaseClassLogic();

	FileLogic fileHandler;
};

#endif