//@author A0111718M
#include "stdafx.h"
#include "CppUnitTest.h"
#include "AddParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace t091c_test
{
	TEST_CLASS(UnitTestParserNL)
	{
	public:
		
		TEST_METHOD(NL_PARSER_CHECK1) // Checks for deadline tasks.
		{
			AddParser test;
			string input = "meeting with boss on 101014 at 1700 @Important";
			ParsedDataPackage output = test.parseNLAndReturn(input);
			string testOutput1 = "meeting with boss";
			string testOutput2 = "10/10/2014";
			string testOutput3 = "17:00";
			string testOutput4 = "Important";
			Assert::AreEqual(output.getLineEntries()[NAME_ATTRIBUTE], testOutput1);
			Assert::AreEqual(output.getLineEntries()[DATE_ATTRIBUTE], testOutput2);
			Assert::AreEqual(output.getLineEntries()[END_ATTRIBUTE], testOutput3);
			Assert::AreEqual(output.getLineEntries()[CATEGORY_ATTRIBUTE], testOutput4);
		}

		TEST_METHOD(NL_PARSER_CHECK2) // Checks for timed tasks.
		{
			AddParser test;
			string input = "meeting with boss on 101014 from 1400 to 1500 @Important";
			ParsedDataPackage output = test.parseNLAndReturn(input);
			string testOutput1 = "meeting with boss";
			string testOutput2 = "10/10/2014";
			string testOutput3 = "14:00";
			string testOutput4 = "15:00";
			string testOutput5 = "Important";
			Assert::AreEqual(output.getLineEntries()[NAME_ATTRIBUTE], testOutput1);
			Assert::AreEqual(output.getLineEntries()[DATE_ATTRIBUTE], testOutput2);
			Assert::AreEqual(output.getLineEntries()[START_ATTRIBUTE], testOutput3);
			Assert::AreEqual(output.getLineEntries()[END_ATTRIBUTE], testOutput4);
			Assert::AreEqual(output.getLineEntries()[CATEGORY_ATTRIBUTE], testOutput5);
		}

		TEST_METHOD(NL_PARSER_CHECK3) // Checks for float tasks.
		{
			AddParser test;
			string input = "meeting with boss on the boat at certain day @Important";
			ParsedDataPackage output = test.parseNLAndReturn(input);
			string testOutput1 = "meeting with boss on the boat at certain day";
			string testOutput2 = "";
			string testOutput3 = "";
			string testOutput4 = "";
			string testOutput5 = "Important";
			Assert::AreEqual(output.getLineEntries()[NAME_ATTRIBUTE], testOutput1);
			Assert::AreEqual(output.getLineEntries()[DATE_ATTRIBUTE], testOutput2);
			Assert::AreEqual(output.getLineEntries()[START_ATTRIBUTE], testOutput3);
			Assert::AreEqual(output.getLineEntries()[END_ATTRIBUTE], testOutput4);
			Assert::AreEqual(output.getLineEntries()[CATEGORY_ATTRIBUTE], testOutput5);
		}

		TEST_METHOD(NL_PARSER_CHECK4) // Checks for date overload.
		{
			AddParser test;
			string input = "meeting with boss on next sunday at 1400 @Important";
			ParsedDataPackage output = test.parseNLAndReturn(input);
			string testOutput1 = "meeting with boss";
			string testOutput2 = "16/11/2014";
			string testOutput3 = "";
			string testOutput4 = "14:00";
			string testOutput5 = "Important";
			Assert::AreEqual(output.getLineEntries()[NAME_ATTRIBUTE], testOutput1);
			Assert::AreEqual(output.getLineEntries()[DATE_ATTRIBUTE], testOutput2);
			Assert::AreEqual(output.getLineEntries()[START_ATTRIBUTE], testOutput3);
			Assert::AreEqual(output.getLineEntries()[END_ATTRIBUTE], testOutput4);
			Assert::AreEqual(output.getLineEntries()[CATEGORY_ATTRIBUTE], testOutput5);
		}

		TEST_METHOD(NL_PARSER_CHECK5) // Checks for time overload to next day.
		{
			AddParser test;
			string input = "meeting with boss on 291114 from 2300 to 0200+1 @Important";
			ParsedDataPackage output = test.parseNLAndReturn(input);
			string testOutput1 = "meeting with boss";
			string testOutput2 = "29/11/2014";
			string testOutput3 = "23:00";
			string testOutput4 = "02:00+1";
			string testOutput5 = "Important";
			Assert::AreEqual(output.getLineEntries()[NAME_ATTRIBUTE], testOutput1);
			Assert::AreEqual(output.getLineEntries()[DATE_ATTRIBUTE], testOutput2);
			Assert::AreEqual(output.getLineEntries()[START_ATTRIBUTE], testOutput3);
			Assert::AreEqual(output.getLineEntries()[END_ATTRIBUTE], testOutput4);
			Assert::AreEqual(output.getLineEntries()[CATEGORY_ATTRIBUTE], testOutput5);
		}

		TEST_METHOD(NL_PARSER_CHECK6) // Checks for deadline tasks without time.
		{
			AddParser test;
			string input = "meeting with boss on 291114 @Important";
			ParsedDataPackage output = test.parseNLAndReturn(input);
			string testOutput1 = "meeting with boss";
			string testOutput2 = "29/11/2014";
			string testOutput3 = "";
			string testOutput4 = "";
			string testOutput5 = "Important";
			Assert::AreEqual(output.getLineEntries()[NAME_ATTRIBUTE], testOutput1);
			Assert::AreEqual(output.getLineEntries()[DATE_ATTRIBUTE], testOutput2);
			Assert::AreEqual(output.getLineEntries()[START_ATTRIBUTE], testOutput3);
			Assert::AreEqual(output.getLineEntries()[END_ATTRIBUTE], testOutput4);
			Assert::AreEqual(output.getLineEntries()[CATEGORY_ATTRIBUTE], testOutput5);
		}

		TEST_METHOD(NL_PARSER_CHECK7) // Checks for no event exception.
		{
			AddParser add;
			try {
				string event = add.extractEventNL("  on 101014 at 1700");
				Assert::IsTrue(false);
			}
			catch (const exception& ex) {
				Assert::IsTrue(true && ex.what());
			}
		}

	// Test examples.

	// meeting with boss on 200515 at 1700
	// on 101014 at 1700
	// meeting with boss on 101214 at 1700
	// watch a midnight movie on 031214 from 2300 to 0030+1
	// on 101014 from 1700 to 1800");
	// on 101014 from 1700 to 1800
	// from 1700 to 1800
	// from 1700 to 1800
	// meeting with boss on 101014 at 17000
	// meeting with boss on 101014 from 17000 to 1800
	// meeting with boss on 101014 from 1700 to 18000
	// meeting with boss on 101014 from 1700 to 1800+1
	// meeting with boss on 200515 from 1700 to 1800 @boss
	// meeting with boss on 200515 from 1700 to 1800 @@meeting
	// meeting with boss on 200515 from 1700 to 1800 -meeting-
	// meeting with boss on tuesday from 1700 to 1800 @meeting
	// meeting with boss on next wed from 1700 to 1800 @meeting
	// meeting with boss on wed from 1700 to 1800 @meeting
			
	};
}
