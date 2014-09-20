#pragma once
#include "stdafx.h"
#include <string>

using namespace std;

class CommandAndArgumentParser
{
private:
	string command;
	string arguments;

public:
	CommandAndArgumentParser(string input);
	~CommandAndArgumentParser();

};

