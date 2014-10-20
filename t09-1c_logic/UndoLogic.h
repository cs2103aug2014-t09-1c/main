#pragma once
#include "BaseClassLogic.h"
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

