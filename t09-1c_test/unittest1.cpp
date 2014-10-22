#include "stdafx.h"
#include "CppUnitTest.h"
#include "AddLogic.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace t091c_test
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			AddLogic test("hello.txt");
			test.appendToLineEntry("date", "fsdfs");
			test.appendToLineEntry("start", "dfsds");
			test.appendToLineEntry("end", "jfhs");
			Assert::IsTrue(test.isDateAndTimeCorrect());
		}
		TEST_METHOD(TestMethod2)
		{
			AddLogic test("hello.txt");
			test.determineType();
			string errorStr = "Invalid Entry";
		//	Assert::AreEqual(errorStr, test.error);
		}

	};
}