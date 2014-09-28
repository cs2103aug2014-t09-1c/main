#pragma once
#include "BaseClassLogic.h"
#define IMPT_MSG_ALARM \
	"Reconfirm your deletion."

class DeleteLogic :
	public BaseClassLogic
{
public:
	void deleteUserInputRelatedMessage(string userInput, string filename);
	~DeleteLogic();
};

