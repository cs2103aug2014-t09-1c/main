#include "stdafx.h"
#include "CppUnitTest.h"
#include "ParsedDataPackage.h"
#include "EditParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace t091c_test
{
	TEST_CLASS(UNIT_TEST_EDIT_PARSER)
	{
	public:
		
		TEST_METHOD(EDIT_PARSER_CHECK1)
		{
			EditParser test;
			string input = "1 [Exam][291114][1100][Important]";
			ParsedDataPackage output = test.parseAndReturn(input);
			int testOutput1 = 1;
			string testOutput2 = "Exam";
			string testOutput3 = "29/11/2014";
			string testOutput4 = "11:00";
			string testOutput5 = "Important";
			Assert::AreEqual(output.getStartEndPositions()[FROM_POSITION], testOutput1);
			Assert::AreEqual(output.getLineEntries()[NAME_ATTRIBUTE], testOutput2);
			Assert::AreEqual(output.getLineEntries()[DATE_ATTRIBUTE], testOutput3);
			Assert::AreEqual(output.getLineEntries()[END_ATTRIBUTE], testOutput4);
			Assert::AreEqual(output.getLineEntries()[CATEGORY_ATTRIBUTE], testOutput5);
		}

	};
}