#pragma once
#include "BaseClassParser.h"
class AddParser :
	public BaseClassParser
{
public:
	AddParser();
	~AddParser();
	static bool checkEntry();
};

