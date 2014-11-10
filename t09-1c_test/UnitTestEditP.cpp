#include "stdafx.h"
#include "CppUnitTest.h"
#include "ParsedDataPackage.h"
#include "EditParser.h"
#include "ProgramController.h"
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
		TEST_METHOD(EDIT_PARSER_CHECK2)
		{
			EditParser test;
			string input = "2 [Mock Exam][301214][1100-1300][Not Important]";
			ParsedDataPackage output = test.parseAndReturn(input);
			int testOutput1 = 2;
			string testOutput2 = "Mock Exam";
			string testOutput3 = "30/12/2014";
			string testOutput4 = "11:00";
			string testOutput5 = "13:00";
			string testOutput6 = "Not Important";
			Assert::AreEqual(output.getStartEndPositions()[FROM_POSITION], testOutput1);
			Assert::AreEqual(output.getLineEntries()[NAME_ATTRIBUTE], testOutput2);
			Assert::AreEqual(output.getLineEntries()[DATE_ATTRIBUTE], testOutput3);
			Assert::AreEqual(output.getLineEntries()[START_ATTRIBUTE], testOutput4);
			Assert::AreEqual(output.getLineEntries()[END_ATTRIBUTE], testOutput5);
			Assert::AreEqual(output.getLineEntries()[CATEGORY_ATTRIBUTE], testOutput6);
		}
		TEST_METHOD(EDIT_PARSER_CHECK3)
		{
			EditParser test;
			string input = "3 [Exam][][][]";
			ParsedDataPackage output = test.parseAndReturn(input);
			int testOutput1 = 3;
			string testOutput2 = "Exam";
			string testOutput3 = "";
			string testOutput4 = "";
			string testOutput5 = "";
			string testOutput6 = "";
			Assert::AreEqual(output.getStartEndPositions()[FROM_POSITION], testOutput1);
			Assert::AreEqual(output.getLineEntries()[NAME_ATTRIBUTE], testOutput2);
			Assert::AreEqual(output.getLineEntries()[DATE_ATTRIBUTE], testOutput3);
			Assert::AreEqual(output.getLineEntries()[START_ATTRIBUTE], testOutput4);
			Assert::AreEqual(output.getLineEntries()[END_ATTRIBUTE], testOutput5);
			Assert::AreEqual(output.getLineEntries()[CATEGORY_ATTRIBUTE], testOutput6);
		}
		TEST_METHOD(EDIT_PARSER_CHECK4)
		{
			EditParser test;
			string input = "4 [Exam][291114][][]";
			ParsedDataPackage output = test.parseAndReturn(input);
			int testOutput1 = 4;
			string testOutput2 = "Exam";
			string testOutput3 = "29/11/2014";
			string testOutput4 = "";
			string testOutput5 = "";
			string testOutput6 = "";
			Assert::AreEqual(output.getStartEndPositions()[FROM_POSITION], testOutput1);
			Assert::AreEqual(output.getLineEntries()[NAME_ATTRIBUTE], testOutput2);
			Assert::AreEqual(output.getLineEntries()[DATE_ATTRIBUTE], testOutput3);
			Assert::AreEqual(output.getLineEntries()[START_ATTRIBUTE], testOutput4);
			Assert::AreEqual(output.getLineEntries()[END_ATTRIBUTE], testOutput5);
			Assert::AreEqual(output.getLineEntries()[CATEGORY_ATTRIBUTE], testOutput6);
		}
		TEST_METHOD(EDIT_PARSER_CHECK5)
		{
			EditParser test;
			string input = "5 [Exam][][][Important]";
			ParsedDataPackage output = test.parseAndReturn(input);
			int testOutput1 = 5;
			string testOutput2 = "Exam";
			string testOutput3 = "";
			string testOutput4 = "";
			string testOutput5 = "";
			string testOutput6 = "Important";
			Assert::AreEqual(output.getStartEndPositions()[FROM_POSITION], testOutput1);
			Assert::AreEqual(output.getLineEntries()[NAME_ATTRIBUTE], testOutput2);
			Assert::AreEqual(output.getLineEntries()[DATE_ATTRIBUTE], testOutput3);
			Assert::AreEqual(output.getLineEntries()[START_ATTRIBUTE], testOutput4);
			Assert::AreEqual(output.getLineEntries()[END_ATTRIBUTE], testOutput5);
			Assert::AreEqual(output.getLineEntries()[CATEGORY_ATTRIBUTE], testOutput6);
		}
		TEST_METHOD(EDIT_PARSER_CHECK6)
		{
			EditParser test;
			string input = "6 [Exam][291114][1300][]";
			ParsedDataPackage output = test.parseAndReturn(input);
			int testOutput1 = 6;
			string testOutput2 = "Exam";
			string testOutput3 = "29/11/2014";
			string testOutput4 = "";
			string testOutput5 = "13:00";
			string testOutput6 = "";
			Assert::AreEqual(output.getStartEndPositions()[FROM_POSITION], testOutput1);
			Assert::AreEqual(output.getLineEntries()[NAME_ATTRIBUTE], testOutput2);
			Assert::AreEqual(output.getLineEntries()[DATE_ATTRIBUTE], testOutput3);
			Assert::AreEqual(output.getLineEntries()[START_ATTRIBUTE], testOutput4);
			Assert::AreEqual(output.getLineEntries()[END_ATTRIBUTE], testOutput5);
			Assert::AreEqual(output.getLineEntries()[CATEGORY_ATTRIBUTE], testOutput6);
		}
		TEST_METHOD(EDIT_PARSER_CHECK7)
		{
			EditParser test;
			string input = "7 [Exam][291114][][Important]";
			ParsedDataPackage output = test.parseAndReturn(input);
			int testOutput1 = 7;
			string testOutput2 = "Exam";
			string testOutput3 = "29/11/2014";
			string testOutput4 = "";
			string testOutput5 = "";
			string testOutput6 = "Important";
			Assert::AreEqual(output.getStartEndPositions()[FROM_POSITION], testOutput1);
			Assert::AreEqual(output.getLineEntries()[NAME_ATTRIBUTE], testOutput2);
			Assert::AreEqual(output.getLineEntries()[DATE_ATTRIBUTE], testOutput3);
			Assert::AreEqual(output.getLineEntries()[START_ATTRIBUTE], testOutput4);
			Assert::AreEqual(output.getLineEntries()[END_ATTRIBUTE], testOutput5);
			Assert::AreEqual(output.getLineEntries()[CATEGORY_ATTRIBUTE], testOutput6);
		}
		TEST_METHOD(EDIT_PARSER_CHECK8)
		{
			EditParser test;
			string consoleString;
			string input = "8 [Exam][29111][][]";
			try{
				ParsedDataPackage output = test.parseAndReturn(input);
				int testOutput1 = 8;
				string testOutput2 = "Exam";
				string testOutput3 = "";
				string testOutput4 = "";
				string testOutput5 = "";
				string testOutput6 = "";

				Assert::AreEqual(output.getStartEndPositions()[FROM_POSITION], testOutput1);
				Assert::AreEqual(output.getLineEntries()[NAME_ATTRIBUTE], testOutput2);
				Assert::AreEqual(output.getLineEntries()[DATE_ATTRIBUTE], testOutput3);
				Assert::AreEqual(output.getLineEntries()[START_ATTRIBUTE], testOutput4);
				Assert::AreEqual(output.getLineEntries()[END_ATTRIBUTE], testOutput5);
				Assert::AreEqual(output.getLineEntries()[CATEGORY_ATTRIBUTE], testOutput6);
			}
			catch (const exception& ex){
				consoleString = ex.what();
			}
			string expectedMessage = "Please enter a valid DDMMYY date!";
			Assert::AreEqual(expectedMessage, consoleString);
		}
	};
}