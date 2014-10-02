#include "stdafx.h"
#include "CommandAndArgumentParser.h"
#include "ParserHelperFunctions.h"


CommandAndArgumentParser::CommandAndArgumentParser(string input)
{
	setCommand(input);
	setArguments(input);
}


CommandAndArgumentParser::~CommandAndArgumentParser()
{
}

void CommandAndArgumentParser::setCommand(string input)
{
	command = getCommand(input);
}

void CommandAndArgumentParser::setArguments(string input)
{
	arguments = getArguments(input);
}

string CommandAndArgumentParser::getCommand(string input)
{
	string command;
	stringstream takeCommand(input);
	takeCommand >> command;
	return command;
}

string CommandAndArgumentParser::getArguments(string input)
{
	string arguments;
	std::string first;
	std::istringstream commandRemover{ input };
	commandRemover >> arguments;

	std::ostringstream oss;
	oss << commandRemover.rdbuf();

	arguments = argumentStringParser(oss.str());

	return arguments;
}

string CommandAndArgumentParser::argumentStringParser(string argument)
{
	if (ParserHelperFunctions::isParameterStringEmpty(argument)) {
		argument = ""; // empty string
	}
	else {
		argument.erase(0, 1); // remove leading whitespace
	}

	return argument;
}

string CommandAndArgumentParser::commandArgumentError()
{
	return COMMANDANDARGUMENT_PARSER_ERROR;
}