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

	int displayCase;

	void initiateLineText();
	void deleteLine(string date, vector<string> keywords, int position);
	bool verifyLine();
	void appendOldCreationDate();
public:
	EditLogic(string fileName, string date, vector<string> keywords, int position, int displayCase);
	~EditLogic();
	bool successfulEdit = false;
	string oldLine;
	int oldPosition;
	
	void appendEntry(string attriibute, string entry);
	void editEntry();
};

#endif

