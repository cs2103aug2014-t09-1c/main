//@author A0111718M
#pragma once
#ifndef COMMANDANDARGUMENT_PARSER
#define COMMANDANDARGUMENT_PARSER

#include "stdafx.h"
#include <string>
#include <sstream>

#define EMPTY_STRING \
	""

using namespace std;

class CommandAndArgumentParser
{
private:
	string command;
	string arguments;

	void setCommand(string input);
	void setArguments(string input);

	/*
	* Clean up arguments by removing leading white space.
	*/
	string argumentStringParser(string argument);
	bool isParameterStringEmpty(string parameter);

public:
	CommandAndArgumentParser(string input);
	~CommandAndArgumentParser();

	string getCommand();
	string getArguments();

};

#endif
