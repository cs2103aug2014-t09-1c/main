#pragma once
#include "BaseClassLogic.h"
#include "ArrangeLogic.h"
#include "CompleteLogic.h"
#include "EditLogic.h"
#include "FileLogic.h"

class CompleteLogic
	public class BaseClassLogic
{

private:
	FileLogic fileHandler;
	int displayCase;

public:
	CompleteLogic(string fileName, int displayCase);
	~CompleteLogicLogic();

	string taskCompleted;
	int completedTaskPosition = -1;
	void CompleteTask(string date, int position);
};

