#include "stdafx.h"
#include "CppUnitTest.h"
#include "AddParser.h"
#include "ParsedDataPackage.h"
#include "TimeParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace t091c_test
{
	TEST_CLASS(UnitTestParserNL)
	{
	public:
		
		TEST_METHOD(Event1)
		{
			AddParser add;
			string event = add.extractEventNL("meeting with boss on 101014 at 1700");
			string expectedEvent = "meeting with boss";
			Assert::AreEqual(expectedEvent, event);
		}

		TEST_METHOD(Event2)
		{
			AddParser add;
			string event = add.extractEventNL("meeting with boss");
			string expectedEvent = "meeting with boss";
			Assert::AreEqual(expectedEvent, event);
		}

		TEST_METHOD(Event3)
		{
			AddParser add;
			string event = add.extractEventNL("meeting with boss on 10101");
			string expectedEvent = "meeting with boss on 10101";
			Assert::AreEqual(expectedEvent, event);
		}

		TEST_METHOD(Event4)
		{
			AddParser add;
			string event = add.extractEventNL("meeting with boss on 1010124");
			string expectedEvent = "meeting with boss on 1010124";
			Assert::AreEqual(expectedEvent, event);
		}

		TEST_METHOD(Event5)
		{
			AddParser add;
			string event = add.extractEventNL("meeting with boss on 101014 on booya");
			string expectedEvent = "meeting with boss on 101014 on booya";
			Assert::AreEqual(expectedEvent, event);
		}

		TEST_METHOD(Event6)
		{
			AddParser add;
			string event = add.extractEventNL("on 101014 at 1700");
			string expectedEvent = "on 101014 at 1700";
			Assert::AreEqual(expectedEvent, event);
		}

		TEST_METHOD(Event7)
		{
			AddParser add;
			string event = add.extractEventNL("  on 101014 at 1700");
			string expectedEvent = "";
			Assert::AreEqual(expectedEvent, event);
		}

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