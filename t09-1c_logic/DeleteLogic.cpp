#include "stdafx.h"
#include "DeleteLogic.h"
#include <string>


void DeleteLogic::deleteLogic(int position, string filename) : fileHander(filename)
{
	FILE *pFile;
	static char tempLine[];//temperary array with undefined size to store each line of undeleted data.
	char *bufferToTakeInData;
	char *ptr;
	int fileSize = FileLogic::getSize();

	bufferToTakeInData = (char*)malloc(fileSize*sizeof(char));//I try to use malloc, but dont know
	memset(bufferToTakeInData,0,fileSize*sizeof(char); //how to determine the size of this buffer
	ptr = bufferToTakeInData;

	string DataToBeDeleted = FileLogic::getLineFromPositionNumber(position);

	pFile = fopen(filename);// How to access the file here?

	if (pFile != NULL){
		while (!feof(pFile)){
			fgets(tempLine,fileSize,pFile); //How to identify the size?
			if (strcmp(tempLine, DataToBeDeleted) != 0){
				strcpy(ptr,tempLine); //put tempLine to buffer
			}
		}
		fclose(pFile);

		pFile = fopen();
		fprintf(pFile,"%s", bufferToTakeInData);
	}
}


DeleteLogic::~DeleteLogic()
{
}
