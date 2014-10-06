#pragma once
#ifndef EDIT_LOGIC
#define EDIT_LOGIC

#include "BaseClassLogic.h"
#include "ArrangeLogic.h"
#include "AddLogic.h"
#include "DeleteLogic.h"

class EditLogic :
	public BaseClassLogic
{
private:
	string fileName;

	string lineText;
	string oldLine;
	int oldPosition;

	void initiateLineText();
	void deleteLine(string date, int position);
	bool verifyLine();
	void appendOldCreationDate();
public:
	EditLogic(string fileName, string date, int position);
	~EditLogic();
	
	void appendEntry(string attriibute, string entry);
	void editEntry();
};

#endif

