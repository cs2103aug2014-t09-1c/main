#pragma once
#include "BaseClassLogic.h"
class SearchLogic :
	public BaseClassLogic
{
public:
	SearchLogic(string userInput);

	string searchKeyWord = userInput;
	if (searchKeyWord != SpecificDate){
		TempFileToStoreSearchedResult = FileLogic.creatNewFile;

		for (lineNumber = 0; LineNumber < file.size(); lineNumber++){
			if (file.getAttributesFromTheLineEntry(LineNumber) == searchKeyWord){
				//add this line to TempFileToStoreSearchedResult;
			}
		}
		cout << TempFileToStoreSearchResult;
	}
	~SearchLogic();
};

