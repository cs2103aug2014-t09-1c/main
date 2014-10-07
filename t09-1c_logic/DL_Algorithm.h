#pragma once

//Damerau_Levenshtein Algorithm class was adapted from 
// http://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance

#ifndef Damerau_Levenshtein_Algorithm
#define Damerau_Levenshtein_Algorithm

#define DELETE_COST \
	1
#define INSERT_COST \
	1
#define REPLACE_COST \
	1
#define SWAP_COST \
	1

#include <iostream>
#include <algorithm>

using namespace std;

class DL_Algorithm
{
public:
	DL_Algorithm();
	~DL_Algorithm();
	int findDLCost(string word, string dictWord);
};

#endif
