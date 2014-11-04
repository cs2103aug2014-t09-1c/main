#pragma once
#ifndef COMMANDANDARGUMENT_PARSER
#define COMMANDANDARGUMENT_PARSER

#include "stdafx.h"
#include <string>
#include <sstream>

#define COMMANDANDARGUMENT_PARSER_ERROR \
	"Unable to Commit. Please refer to \"help\" for guide to input."

using namespace std;

class CommandAndArgumentParser
{
private:
	string command;
	string arguments;

	void setCommand(string input);
	void setArguments(string input);
	string argumentStringParser(string argument);

public:
	CommandAndArgumentParser(string input);
	~CommandAndArgumentParser();


	string getCommand();
	string getArguments();
};

#endif
