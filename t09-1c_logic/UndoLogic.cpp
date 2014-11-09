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
	undoCase.push(ADD_CASE);
	
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
	undoCase.push(MODIFY_CASE);
	
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
	if (commandType == DELETE_CASE) {
		clearRedo();
		undoCase.push(DELETE_CASE);
		undoLineStack.push(lines);
		undoFilePositionStack.push(filePositions);
	}
	else if (commandType == MODIFY_CASE) {
		clearRedo();
		undoCase.push(MODIFY_CASE);
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

		if (caseType == ADD_CASE) {
			modify(fileName, UNDO, ADD_CASE);
		}
		else if (caseType == MODIFY_CASE) {
			modify(fileName, UNDO, MODIFY_CASE);
		}
		else if (caseType == DELETE_CASE) {
			modify(fileName, UNDO, DELETE_CASE);
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

		if (caseType == ADD_CASE) {
			modify(fileName, REDO, ADD_CASE);
		}
		else if (caseType == MODIFY_CASE) {
			modify(fileName, REDO, MODIFY_CASE);
		}
		else if (caseType == DELETE_CASE) {
			modify(fileName, REDO, DELETE_CASE);
		}
	}
}

void UndoLogic::modify(string fileName, string action, string commandType)
{
	stack<stack<string>> * fromLineStack;
	stack<stack<int>> * fromFilePositionStack;
	stack<stack<string>> * toLineStack;
	stack<stack<int>> * toFilePositionStack;

	if (action == UNDO) {
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
		if (commandType == MODIFY_CASE || 
		(commandType == DELETE_CASE && action == REDO) ||
		(commandType == ADD_CASE && action == UNDO)) {
			string oldLine = fileHandler.getLineFromPositionNumber(position);
			oldLinesStore.push(oldLine);
			fileHandler.deleteLine(position);
		}
		if (commandType == MODIFY_CASE || 
		(commandType == DELETE_CASE && action == UNDO) ||
		(commandType == ADD_CASE && action == REDO)) {
			if (commandType == DELETE_CASE || commandType == ADD_CASE) {
				oldLinesStore.push(line);
			}
			fileHandler.addToPositionNumber(position, line);
		}
	}
	toLineStack->push(oldLinesStore);
	toFilePositionStack->push(positionsStore);
}