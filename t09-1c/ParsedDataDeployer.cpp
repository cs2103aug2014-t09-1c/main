#include "stdafx.h"
#include "ParsedDataDeployer.h"
#include "CommandAndArgumentParser.h"


ParsedDataDeployer::ParsedDataDeployer()
{
}


ParsedDataDeployer::~ParsedDataDeployer()
{
}

string ParsedDataDeployer::SendToParser(string input)
{
	return CommandAndArgumentParser::commandParser(input);
}


