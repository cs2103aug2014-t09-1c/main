#include "stdafx.h"
#include "UndoLogic.h"

UndoLogic* UndoLogic::_instance = 0;

UndoLogic::UndoLogic()
{
}


UndoLogic::~UndoLogic()
{
}

UndoLogic* UndoLogic::instance()
{
	if (_instance == 0) {
		_instance = new UndoLogic();
	}
	return _instance;
}

void UndoLogic::reset()
{
	_instance = new UndoLogic();
}

bool UndoLogic::isUndoEmpty()
{
	return undoCase.empty();
}

bool UndoLogic::isRedoEmpty()
{
	return redoCase.empty();
}

void UndoLogic::clearRedo()
{
	redoLineStack = stack<stack<string>>();
	redoFilePositionStack = stack<stack<int>>();
	redoCase = stack<string>();
}

void UndoLogic::clearAll()
{
	undoLineStack = stack<stack<string>>();
	undoFilePositionStack = stack<stack<int>>();
	undoCase = stack<string>();
	clearRedo();
}

void UndoLogic::checkFile(string fileName)
{
	if (this->fileName != fileName) {
		this->fileName = fileName;
		clearAll();
	}
}

void UndoLogic::storeUndo(string fileName)
{
	checkFile(fileName);
	clearRedo();
	undoCase.push("add");
	
	FileLogic fileHandler(fileName);
	int position = fileHandler.getSize() - 1;
	string line = fileHandler.getLineFromPositionNumber(position);
	
	stack<string> addString;
	addString.push(line);
	stack<int> positionStack;
	positionStack.push(position);
	
	undoLineStack.push(addString);
	undoFilePositionStack.push(positionStack);
}

void UndoLogic::storeUndo(string fileName, string line, int position)
{
	checkFile(fileName);
	clearRedo();
	undoCase.push("modify");
	
	stack<string> lineEntry;
	lineEntry.push(line);
	undoLineStack.push(lineEntry);

	stack<int> linePosition;
	linePosition.push(position);
	undoFilePositionStack.push(linePosition);

}

void UndoLogic::storeUndo(string fileName, string commandType, stack<string> lines, stack<int> filePositions)
{
	checkFile(fileName);
	if (commandType == "delete") {
		clearRedo();
		undoCase.push("delete");
		undoLineStack.push(lines);
		undoFilePositionStack.push(filePositions);
	}
	else if (commandType == "modify") {
		clearRedo();
		undoCase.push("modify");
		undoLineStack.push(lines);
		undoFilePositionStack.push(filePositions);
	}
}

void UndoLogic::undo(string fileName)
{
	checkFile(fileName);
	if (!isUndoEmpty()) {
		string caseType = undoCase.top();
		undoCase.pop();
		redoCase.push(caseType);

		if (caseType == "add") {
			modify(fileName, "undo", "add");
		}
		else if (caseType == "modify") {
			modify(fileName, "undo", "modify");
		}
		else if (caseType == "delete") {
			modify(fileName, "undo", "delete");
		}
	}
}

void UndoLogic::redo(string fileName)
{
	checkFile(fileName);
	if (!isRedoEmpty()) {
		string caseType = redoCase.top();
		redoCase.pop();
		undoCase.push(caseType);

		if (caseType == "add") {
			modify(fileName, "redo", "add");
		}
		else if (caseType == "modify") {
			modify(fileName, "redo", "modify");
		}
		else if (caseType == "delete") {
			modify(fileName, "redo", "delete");
		}
	}
}

void UndoLogic::modify(string fileName, string action, string commandType)
{
	stack<stack<string>> * fromLineStack;
	stack<stack<int>> * fromFilePositionStack;
	stack<stack<string>> * toLineStack;
	stack<stack<int>> * toFilePositionStack;

	if (action == "undo") {
		fromLineStack = &undoLineStack;
		fromFilePositionStack = &undoFilePositionStack;
		toLineStack = &redoLineStack;
		toFilePositionStack = &redoFilePositionStack;
	}
	else {
		fromLineStack = &redoLineStack;
		fromFilePositionStack = &redoFilePositionStack;
		toLineStack = &undoLineStack;
		toFilePositionStack = &undoFilePositionStack;
	}

	FileLogic fileHandler(fileName);
	stack<string> lines = fromLineStack->top();
	fromLineStack->pop();
	stack<int> positions = fromFilePositionStack->top();
	fromFilePositionStack->pop();

	stack<string> oldLinesStore;
	stack<int> positionsStore;

	while (!lines.empty() && !positions.empty()) {
		string line = lines.top();
		lines.pop();
		int position = positions.top();
		positions.pop();
		positionsStore.push(position);
		if (commandType == "modify" || 
		(commandType == "delete" && action == "redo") ||
		(commandType == "add" && action == "undo")) {
			string oldLine = fileHandler.getLineFromPositionNumber(position);
			oldLinesStore.push(oldLine);
			fileHandler.deleteLine(position);
		}
		if (commandType == "modify" || 
		(commandType == "delete" && action == "undo") ||
		(commandType == "add" && action == "redo")) {
			if (commandType == "delete" || commandType == "add") {
				oldLinesStore.push(line);
			}
			fileHandler.addToPositionNumber(position, line);
		}
	}
	toLineStack->push(oldLinesStore);
	toFilePositionStack->push(positionsStore);
}