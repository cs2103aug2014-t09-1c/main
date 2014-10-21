#include "stdafx.h"
#include "UndoLogic.h"
#include <stack>


UndoLogic::UndoLogic()
{
	
}


UndoLogic::~UndoLogic()
{
}

void UndoLogic:: executeCommand(int position, string command)
{
	std::stack<int>positionStack:
	std::stack<string>commanStack;
	
	// Execute command
	
	bool CommandExcuted = command->execute();

	// If command complete successfully store in the
	// undo stack
	if (CommandExcuted)
	{
		positionStack.push(position);
		commandStack.push(command);
	}

}

void UndoLogic:: undoCommand(stack positionStack, stack commandStack)
{
	positionStack.pop();
	commandStack.pop();
}

