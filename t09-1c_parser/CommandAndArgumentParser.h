#pragma once
#include "stdafx.h"
#include <string>
#include <sstream>

#define COMMANDANDARGUMENT_PARSER_ERROR \
	"Unable to Commit. Please refer to \"help\" for guide to input."

using namespace std;

class CommandAndArgumentParser
{

public:
	string command;
	string arguments;

	CommandAndArgumentParser(string input);
	~CommandAndArgumentParser();

	void setCommand(string input);
	void setArguments(string input);

	string getCommand(string input);
	string getArguments(string input);
	string argumentStringParser(string argument);

	string commandArgumentError();

	//void commandParser(string command, string arguments);

	//void moveToAddParser(string arguments);
	//void moveToDeleteParser(string arguments);
	//void moveToEditParser(string arguments);
};

