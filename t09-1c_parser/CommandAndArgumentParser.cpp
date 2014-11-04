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
	string command;
	stringstream takeCommand(input);
	takeCommand >> command;
	this->command = command;
}

void CommandAndArgumentParser::setArguments(string input)
{
	string arguments;
	std::string first;
	std::istringstream commandRemover{ input };
	commandRemover >> arguments;

	std::ostringstream oss;
	oss << commandRemover.rdbuf();

	arguments = argumentStringParser(oss.str());

	this->arguments = arguments;
}

string CommandAndArgumentParser::getCommand()
{
	return command;
}

string CommandAndArgumentParser::getArguments()
{
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