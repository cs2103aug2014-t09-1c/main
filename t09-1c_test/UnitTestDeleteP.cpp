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
		
		TEST_METHOD(DELETE_PARSER_ONE_ENTRY)//correct
		{
			DeleteParser test;
			string input = "10";
			ParsedDataPackage output = test.parseAndReturn(input);
			int testOutput = 10;
			Assert::AreEqual(output.getStartEndPositions()[FROM_POSITION], testOutput);
			Assert::AreEqual(output.getStartEndPositions()[TO_POSITION], testOutput);
		}

		TEST_METHOD(DELETE_PARSER_PARSE_FAIL)
		{
			DeleteParser test;
			string input = "abc";
			try {
				ParsedDataPackage output = test.parseAndReturn(input);
				Assert::IsTrue(false);
			}
			catch (const exception& ex) {
				Assert::IsTrue(true && ex.what());
			}
		}
		

	};
}