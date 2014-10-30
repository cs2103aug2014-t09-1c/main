#include "stdafx.h"
#include "DL_Algorithm.h"
#include <vector>
#include <map>
#include <climits>


DL_Algorithm::DL_Algorithm()
{
}


DL_Algorithm::~DL_Algorithm()
{
}

int DL_Algorithm::findDLCost(string word, string dictWord) 
{
	if (word.length() == 0) {
		return dictWord.length() * INSERT_COST;
	}
	if (dictWord.length() == 0) {
		return word.length() * DELETE_COST;
	}

	vector<vector<int>> charTable(word.length(), vector<int>(dictWord.length()));

	map<char, int> charIndexSource;
	if (tolower(word.at(0)) != tolower(dictWord.at(0))) {
		charTable[0][0] = min(REPLACE_COST, DELETE_COST + INSERT_COST);
	}
	charIndexSource.insert(pair<char,int>(word.at(0), 0));

	for (size_t i = 1; i < word.length(); ++i) {
		int deleteDist = charTable[i - 1][0] + DELETE_COST;
		int insertDist = (i + 1) * DELETE_COST + INSERT_COST;
		int matchDist = i * DELETE_COST + (tolower(word.at(i)) == tolower(dictWord.at(0)) ? 0 : REPLACE_COST);
		charTable[i][0] = min(min(deleteDist, insertDist), matchDist);
	}

	for (size_t j = 1; j < dictWord.length(); ++j) {
		int deleteDist = (j + 1) * INSERT_COST + DELETE_COST;
		int insertDist = charTable[0][j - 1] + INSERT_COST;
		int matchDist = j * INSERT_COST + (tolower(word.at(0)) == tolower(dictWord.at(j)) ? 0 : REPLACE_COST);
		charTable[0][j] = min(min(deleteDist, insertDist), matchDist);
	}

	for (size_t i = 1; i < word.length(); ++i) {
		int sourceLetterMatchIndexMax = tolower(word.at(i)) == tolower(dictWord.at(0)) ? 0 : -1;
		for (size_t j = 1; j < dictWord.length(); ++j) {
			int swapCandidateIndex = charIndexSource[dictWord.at(j)];
			int jToSwap = sourceLetterMatchIndexMax;
			int deleteDist = charTable[i - 1][j] + DELETE_COST;
			int insertDist = charTable[i][j - 1] + INSERT_COST;
			int matchDistance = charTable[i - 1][j - 1];
			if (tolower(word.at(i)) != tolower(dictWord.at(j))) {
				matchDistance += REPLACE_COST;
			}
			else {
				sourceLetterMatchIndexMax = j;
			}
			
			int distanceSwap;
			if (swapCandidateIndex != NULL && jToSwap != -1) {
				int iToSwap = swapCandidateIndex;
				int beforeSwapCost;
				if (iToSwap == 0 && jToSwap == 0) {
					beforeSwapCost = 0;
				}
				else {
					beforeSwapCost = charTable[max(0, iToSwap - 1)][max(0, jToSwap - 1)];
				}
				distanceSwap = beforeSwapCost + (i - iToSwap - 1) * DELETE_COST + (j - jToSwap - 1) * INSERT_COST + SWAP_COST;
			}
			else {
				distanceSwap = INT_MAX;
			}

			charTable[i][j] = min(min(min(deleteDist, insertDist), matchDistance), distanceSwap);
		}
		charIndexSource.insert(pair<char,int>(tolower(word.at(i)), i));
	}
	return charTable[word.length() - 1][dictWord.length() - 1];
}
