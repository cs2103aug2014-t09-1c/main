//@author A0111718M
#include "stdafx.h"
#include "CommandAndArgumentParser.h"
#include <algorithm>

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
	std::transform(this->command.begin(), this->command.end(), this->command.begin(), ::tolower);
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
	if (isParameterStringEmpty(argument)) {
		argument = EMPTY_STRING;
	}
	else {
		argument.erase(0, 1); // remove leading whitespace
	}

	return argument;
}

bool CommandAndArgumentParser::isParameterStringEmpty(string parameter)
{
	return parameter.find_first_not_of(' ') == std::string::npos;
}