#include "stdafx.h"
#include "CppUnitTest.h"
#include "ParsedDataPackage.h"
#include "EditParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace t091c_test
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			EditParser test;
			string input = "1 [Exam][291114][1100][Important]";
			vector<ParsedDataPackage> output = test.parseAndReturn(input);
			int testOutput1 = 1;
			string testOutput2 = "Exam";
			string testOutput3 = "29/11/2014";
			string testOutput4 = "11:00";
			string testOutput5 = "Important";
			Assert::AreEqual(output[0].lineNum, testOutput1);
			Assert::AreEqual(output[1].name, testOutput2);
			Assert::AreEqual(output[1].date, testOutput3);
			Assert::AreEqual(output[1].end, testOutput4);
			Assert::AreEqual(output[1].category, testOutput5);
		}

	};
}