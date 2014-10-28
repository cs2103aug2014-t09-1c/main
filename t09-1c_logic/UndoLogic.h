#pragma once
#ifndef UNDO_LOGIC
#define UNDO_LOGIC

#include "BaseClassLogic.h"
#include "stack"

class UndoLogic :
	public BaseClassLogic
{
private:
	static UndoLogic* _instance;
	string fileName;

	stack <stack<string>> undoLineStack;
	stack <stack<int>> undoFilePositionStack;
	stack <string> undoCase;

	stack <stack<string>> redoLineStack;
	stack <stack<int>> redoFilePositionStack;
	stack <string> redoCase;

	void clearRedo();
	void clearAll();
	void checkFile(string fileName);
	void modify(string fileName, string action, string commandType);

protected:
	UndoLogic();
	~UndoLogic();
	
public:
	static UndoLogic* instance();
	static void reset();
	bool isUndoEmpty();
	bool isRedoEmpty();

	// add case
	void storeUndo(string fileName);
	// edit case
	void storeUndo(string fileName, string line, int position);
	// delete case/complete case
	void storeUndo(string fileName, string commandType, stack<string> lines, stack<int> filePositions);

	
	void undo(string fileName);
	void redo(string fileName);
};

#endif
