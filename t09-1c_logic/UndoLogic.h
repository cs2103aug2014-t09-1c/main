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
	stack <stack<string>> lineStack;
	stack <stack<int>> filePositionStack;

	stack <string> undoCase;

	void undoAdd(string fileName);
	void undoEdit(string fileName);
	void undoDelete(string fileName);
	void undoCompleter(string fileName, string commandType);
	

protected:
	UndoLogic();
	~UndoLogic();
	
public:
	static UndoLogic* instance();
	static void reset();
	bool isUndoEmpty();

	// add case
	void storeUndo();
	// edit case
	void storeUndo(string line, int position);
	// delete case
	void storeUndo(stack<string> lines, stack<int> filePositions);
	//complete/unomplete case
	void storeUndo(string commandCase, stack<int> filePositions);
	
	void undo(string fileName);
};

#endif
