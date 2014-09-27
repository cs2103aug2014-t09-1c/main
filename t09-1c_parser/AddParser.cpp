#include "stdafx.h"
#include "AddParser.h"

// Syntax: [eventName] <start> <end> <rating> <@category@>

AddParser::AddParser()
{
}


AddParser::~AddParser()
{
}

string AddParser::argumentError()
{
	string errorMessage = "Unable to Commit. Please refer to \"help\" for guide to input. \n";
	return errorMessage;
}

void AddParser::setArguments(string input)
{
	arguments = input;
}

string AddParser::extractEventName(string arguments)
{
	string eventName;
	size_t position1 = arguments.find('[');
	size_t position2 = arguments.find(']');

	if (position1 == -1 || position2 == -1) {
		return argumentError();
	}
	else if (position2 - position1 == 1) {
		eventName = "-";
		return eventName;
	}
	else {
		eventName = arguments.substr(position1 + 1, position2 - position1 - 1);
		return eventName;
	}
}

string AddParser::extractStart(string arguments)
{
	string start;
	size_t reference1 = arguments.find(']'); // I assume start is behind [eventName] <start>
	size_t reference2 = arguments.find("/", reference1 + 1, 1); // I'm finding "/" from dd/mm
	size_t reference3 = arguments.find(":", reference1 + 1, 1); // I'm finding ":" from HH:MM

	// dd/mm/yyyy HH:MM has 16 characters
	if (reference1 == -1 || reference2 == -1 || reference3 == -1 ||
		reference3 - reference2 + 5 != 16) {
		return argumentError();
	}
	else {
		start = arguments.substr(reference2 - 2, 16);
		return start;
	}
}

string AddParser::extractEnd(string arguments)
{
	string end;
	size_t reference1 = arguments.find(']'); // to start searching key words behind [eventName]
	size_t reference2 = arguments.find("to", reference1 + 1, 2);
	size_t reference3 = arguments.find("by", reference1 + 1, 2);

	if (reference1 == -1) {
		return argumentError();
	}
	else if (reference2 == -1 && reference3 == -1) {
		end = "-";
		return end;
	}
	else {
		if (reference2 != -1) {
			end = arguments.substr(reference2 + 3, 16);
			return end;
		}
		else {
			end = arguments.substr(reference3 + 3, 16);
			return end;
		}
	}
}

string AddParser::extractRating(string arguments)
{
	string rating;
	size_t reference1 = arguments.find(']'); // to start searching key word "rating" behind [eventName]
	size_t reference2 = arguments.find("rating", reference1 + 1, 6);

	if (reference1 == -1 || reference2 == -1) {
		return argumentError();
	}
	// catching out of range exception if user ends input with "...rating"
	else if (reference2 + 6 > arguments.length()) {
		rating = "1";
		return rating;
	}
	else {
		rating = arguments.substr(reference2 + 7, 1);

		// if rating parsed white space (e.g user input "rating     ", what will be the value of found?
		size_t found = rating.find_first_not_of("123");

		if (found == -1) {
			return rating;
		}
		// if rating parsed a non-numeric value, put rating default to 1
		else {
			rating = "1";
			return rating;
		}
	}
}

string AddParser::extractCategory(string arguments)
{
	string category;

	size_t reference1 = arguments.find(']'); // start search after [eventName]
	size_t reference2 = arguments.find("@", reference1 + 1, 1); // find first occurence of @
	size_t reference3 = arguments.find("@", reference2 + 1, 1); // find second occurence of @

	if (reference1 == -1) {
		return argumentError();
	}
	else if (reference2 == -1) {
		category = "";
		return category;
	}
	else {
		category = arguments.substr(reference2 + 1, reference3 - reference2 - 1);
		return category;
	}
}