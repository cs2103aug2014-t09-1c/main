#pragma once
#include "BaseClassLogic.h"
#include "stack"
class UndoLogic :
	public BaseClassLogic
{
public:
	UndoLogic();

	stack <string> UndoStack;
	void executeCommand(command);
	void UndoCommand();
	~UndoLogic();
};

