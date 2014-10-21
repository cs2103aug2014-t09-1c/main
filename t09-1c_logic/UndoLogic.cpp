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
	std::stack<char>commanStack;
	
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
	int positionUndo = positionStack.pop();
	char commandUndo = commandStack.pop();

	if (strcmp(commandUndo, "add") != 0){
		DeleteLogic::deleteEntry(date, undoPosition);
	}
	else if (strcmp(commanUndo, "delete") != 0){
		//add accordingly
	}
	//how to do undo with edit?
}

