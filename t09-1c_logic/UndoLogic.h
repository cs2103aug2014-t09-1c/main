#pragma once
#include "BaseClassLogic.h"
class UndoLogic :
	public BaseClassLogic
{
public:
	UndoLogic();

	bool executeCommand(command_ptr_t command);
	void UndoFunction();
	~UndoLogic();
};

