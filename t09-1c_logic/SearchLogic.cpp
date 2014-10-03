#include "stdafx.h"
#include "SearchLogic.h"
#include "AddLogic.h"
#include "FileEntryFormatter.h"


SearchLogic::SearchLogic(FileLogic fileHandler) : fileHandler(""), addFunction(fileHandler)
{
	this->fileHandler = fileHandler;
}


SearchLogic::~SearchLogic(){
}
		



		//user is searching for the list of the task of a certain day
string SearchLogic::searchEntryDate(string date){
	return arranger.getListOfDate(date);
}





string SearchLogic::searchEntry(string userEntry)
{
	if (!addFuntion.isEntryValid()){
		//return error message?
	}

	else{
		string resultedLine = searchForLineInFile(userEntry);
	}
}



//implementation of leveshlein algorithm
string SearchLogic::searchForLineInFile(string userEntry)
{

	int fileSize = FileLogic::getSize();
	int positionOfCurrentLine;
	int len1 = userEntry.length();

	using std::fmin;

	//This loop is to search for the wanted data line by line. 
	for (positionOfCurrentLine = 0; positionOfCurrentLine < fileSize; positionOfCurrentLine++){
		string currentLine = FileLogic::getLineFromPositionNumber(positionOfCurrentLine);
		int len2 = currentLine.length();
		//size of the array is determined by the size of 2 strings.
		//im not sure if the user input is a line of entry or just the key attributes? should it compare 2 line of data?
		//if the user only enter key attributes, how do i extract each attribute from the task and compare with the user input?
		int count[len1 + 1][len2 + 1];

		for (int i = 0; i < count.length(); i++){
			for (int j = 0; j < count[i].length(); j++){
				if (i == 0){
					count[i][j] = j;
				}
				else{
					if (j == 0){
						count[i][j] = i;
					}
					else{
						count[i][j] = 0;
					}
				}
				if (i > 0 && j > 0){
					if (userEntry.at(i - 1) == currentLine.at(j - 1)){
						count[i][j] = count[i - 1][j - 1];
					}
					else{
						count[i][j] = fmin(count[i - 1][j] + 1, fmin(count[i][j - 1] + 1, count[i - 1][j - 1] + 1));
					}
				}

			}
		}

		//cound == 0 means the wanted data is found, return it
		if (count[count.length() - 1][count(0).length_1] == 0){
			string lineFound = FileLogic::getLineFromPositionNumber(positionOfCurrentLine);
			return lineFound;
		}
	}


}
