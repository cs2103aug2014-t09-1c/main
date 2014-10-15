#include "stdafx.h"
#include "UndoLogic.h"
#include<stack>


UndoLogic::UndoLogic()
{
	stack <string> UndoStack;
}


UndoLogic::~UndoLogic()
{
}

void UndoLogic:: executeCommand(command_ptr_t command)
{
	// Execute command
	bool CommandExcuted = command->execute();

	// If command complete successfully store in the
	// undo stack
	if (CommandExcuted)
	{
		UndoStack.push(command);
	}

}

void UndoLogic:: undoCommand()
{
	UndoStack.pop();
}

