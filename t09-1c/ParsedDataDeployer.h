#pragma once
#include <string>
#include <sstream>
#include "CommandAndArgumentParser.h"


using namespace std;

class ParsedDataDeployer
{
private:
	string command;
public:
	ParsedDataDeployer();
	~ParsedDataDeployer();

	string ParsedDataDeployer::SendToParser(string input);

	
};

