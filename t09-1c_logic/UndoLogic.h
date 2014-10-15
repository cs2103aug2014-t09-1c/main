#pragma once
#include "BaseClassLogic.h"
class UndoLogic :
	public BaseClassLogic
{
public:
	UndoLogic();

	void executeCommand(command_ptr_t command);
	void UndoCommand();
	~UndoLogic();
};

