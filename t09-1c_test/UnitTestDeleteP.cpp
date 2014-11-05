#include "stdafx.h"
#include "CppUnitTest.h"
#include "DeleteParser.h"
#include "ParsedDataPackage.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace t091c_test
{
	TEST_CLASS(UnitTest2)
	{
	public:
		
		//TEST_METHOD(TestMethod1a)//correct
		//{
		//	DeleteParser test;
		//	string input = "10";
		//	ParsedDataPackage output = test.parseAndReturn(input);
		//	ParsedDataPackage testOutput;
		//	testOutput.lineNum = 10;
		//	Assert::AreEqual(output.lineNum, testOutput.lineNum);
		//}
		/*TEST_METHOD(TestMethod1b)//no change
		{
			DeleteParser test;
			string input = "abc";
			ParsedDataPackage output;
			output.lineNum = 0;
			output = test.parseAndReturn(input);
			ParsedDataPackage testOutput;
			testOutput.lineNum = 0;
			Assert::AreEqual(output.lineNum, testOutput.lineNum);
		}*/
		

	};
}