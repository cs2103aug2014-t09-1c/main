#include "stdafx.h"
#include "UndoLogic.h"
#include <stack>
#include "FileLogic.h"
#include "FileEntryFormatter.h"

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
	_instance = new UndoLogic;
}

bool UndoLogic::isUndoEmpty()
{
	return undoCase.empty();
}

void UndoLogic::storeUndo()
{
	undoCase.push("add");
}

void UndoLogic::storeUndo(string line, int position)
{
	undoCase.push("edit");
	
	stack<string> lineEntry;
	lineEntry.push(line);
	lineStack.push(lineEntry);

	stack<int> linePosition;
	linePosition.push(position);
	filePositionStack.push(linePosition);

}

void UndoLogic::storeUndo(stack<string> lines, stack<int> filePositions)
{
	undoCase.push("delete");
	lineStack.push(lines);
	filePositionStack.push(filePositions);
}

void UndoLogic::storeUndo(string commandCase, stack<int> filePositions)
{
	if (commandCase == "complete" || commandCase == "uncomplete") {
		undoCase.push(commandCase);
		filePositionStack.push(filePositions);
	}
}

void UndoLogic::undo(string fileName)
{
	if (!isUndoEmpty()) {
		string caseType = undoCase.top();
		undoCase.pop();

		if (caseType == "add") {
			undoAdd(fileName);
		}
		else if (caseType == "edit") {
			undoEdit(fileName);
		}
		else if (caseType == "delete") {
			undoDelete(fileName);
		}
		else if (caseType == "complete") {
			undoCompleter(fileName, "complete");
		}
		else if (caseType == "uncomplete") {
			undoCompleter(fileName, "uncomplete");
		}
	}
}

void UndoLogic::undoAdd(string fileName)
{
	FileLogic fileHandler(fileName);
	int lastLine = fileHandler.getSize() - 1;
	fileHandler.deleteLine(lastLine);
}

void UndoLogic::undoEdit(string fileName)
{
	FileLogic fileHandler(fileName);
	int position = filePositionStack.top().top();
	filePositionStack.pop();
	string line = lineStack.top().top();
	lineStack.pop();
	fileHandler.deleteLine(position);
	fileHandler.addToPositionNumber(position, line);
}

void UndoLogic::undoDelete(string fileName)
{
	FileLogic fileHandler(fileName);
	stack<string> lines = lineStack.top();
	lineStack.pop();
	stack<int> positions = filePositionStack.top();
	filePositionStack.pop();
	while (!lines.empty() && !positions.empty()) {
		string line = lines.top();
		lines.pop();
		int position = positions.top();
		positions.pop();
		fileHandler.addToPositionNumber(position, line);
	}
}

void UndoLogic::undoCompleter(string fileName, string commandType)
{
	string undoToEntry = "no";
	if (commandType == "uncomplete") {
		undoToEntry = "yes";
	}
	
	FileLogic fileHandler(fileName);
	stack<int> positions = filePositionStack.top();
	filePositionStack.pop();
	while (!positions.empty()) {
		int position = positions.top();
		positions.pop();
		string line = fileHandler.getLineFromPositionNumber(position);
		line = FileEntryFormatter::editAttributedEntryFromLineEntry("complete", undoToEntry, line);
		fileHandler.deleteLine(position);
		fileHandler.addToPositionNumber(position, line);
	}
}