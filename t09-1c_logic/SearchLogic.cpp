#include "stdafx.h"
#include "SearchLogic.h"
#include "AddLogic.h"
#include "FileEntryFormatter.h"
#include "FileLogic.h"
#include "TimeLogic.h"


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
	string specificKeyWord = userEntry;
	if (TimeLogic.isDateValid(specificKeyWord)){
		searchEntryDate;
	}

	else{
		FILE TempFileToStoreSearchedResult = FileLogic.creatNewFile;
		string resultedLine = searchForLineInFile(specificKeyWord);
		FileLogic.appendToFile(string resultedLine);
	}
	cout << "Temperary File To Store Search Result";
}



//implementation of leveshlein algorithm
string SearchLogic::searchForLineInFile(string specificKeyWord)
{
	
	int fileSize = FileLogic.getSize();
	int positionOfCurrentLine;
	int len1 = specificKeyWord.length();

	using std::fmin;

	//This loop is to search for the wanted data line by line. 
	for (positionOfCurrentLine = 0; positionOfCurrentLine < fileSize; positionOfCurrentLine++){
		string currentLine = FileLogic.getLineFromPositionNumber(positionOfCurrentLine);
		int len2 = currentLine.length();
		int count[50][50];// I dont know the size of the array. because it depends on each line of the
						  //file. so the size is not constant. how to do with it?
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
					if (specificKeyWord.at(i - 1) == currentLine.at(j - 1)){
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
			string lineFound = FileLogic.getLineFromPositionNumber(positionOfCurrentLine);
			return lineFound;
		}
	}


}


/*
string searchKeyWord = userInput;
if (searchKeyWord != SpecificDate){
TempFileToStoreSearchedResult = FileLogic.creatNewFile;

for (lineNumber = 0; LineNumber < file.size(); lineNumber++){
if (file.getAttributesFromTheLineEntry(LineNumber) == searchKeyWord){
//add this line to TempFileToStoreSearchedResult;
}
}
cout << TempFileToStoreSearchResult;
} */

