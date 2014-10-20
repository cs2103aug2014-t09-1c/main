#include "stdafx.h"
#include "UndoLogic.h"
#include<stack>


UndoLogic::UndoLogic()
{
	
}


UndoLogic::~UndoLogic()
{
}

void UndoLogic:: executeCommand()
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

