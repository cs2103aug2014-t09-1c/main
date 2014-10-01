#pragma once
#include "AddParser.h"
#include "DeleteParser.h"
#include "EditParser.h"
#include "stdafx.h"
#include <string>
#include <sstream>

using namespace std;

class CommandAndArgumentParser
{

public:
	string command;
	string arguments;

	CommandAndArgumentParser(string input);
	~CommandAndArgumentParser();

	// I assumed UI sends the input string to CommandAndArgumentParser(string input)?
	// input = what user typed in the commit box?
	void setCommand(string input);
	void setArguments(string input);

	string getCommand(string input);
	string getArguments(string input);
	string argumentStringParser(string argument);

	string commandArgumentError();
	void commandParser(string command, string arguments);

	void moveToAddParser(string arguments);
	void moveToDeleteParser(string arguments);
	void moveToEditParser(string arguments);
};

