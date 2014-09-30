#include "stdafx.h"
#include "CommandAndArgumentParser.h"


CommandAndArgumentParser::CommandAndArgumentParser(string input)
{
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
	if (isParameterStringEmpty(argument)) {  // I don't know how to use the VariableHelperFunction class from t09-1c project.
		argument = ""; // empty string
	}
	else {
		argument.erase(0, 1); // remove leading whitespace
	}

	return argument;
}

string CommandAndArgumentParser::commandArgumentError()
{
	string errorMessage = "Unable to Commit. Please refer to \"help\" for guide to input. \n";
	return errorMessage;
}

void CommandAndArgumentParser::commandParser(string command, string arguments)
{
	if (command == "add") moveToAddParser(arguments);
	else if (command == "delete") moveToDeleteParser(arguments);
	else if (command == "edit") moveToEditParser(arguments);

	else commandArgumentError();
}

void CommandAndArgumentParser::moveToAddParser(string arguments)
{
	add.setArguments(arguments);
}

void CommandAndArgumentParser::moveToDeleteParser(string arguments)
{
	del.setArguments(arguments);
}

void CommandAndArgumentParser::moveToEditParser(string arguments)
{
	edit.setArguments(arguments);
}