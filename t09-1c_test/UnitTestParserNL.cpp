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
			string event = add.extractEvent("meeting with boss on 101014 at 1700");
			string expectedEvent = "meeting with boss";
			Assert::AreEqual(expectedEvent, event);
		}

		TEST_METHOD(Event2)
		{
			AddParser add;
			string event = add.extractEvent("meeting with boss");
			string expectedEvent = "";
			Assert::AreEqual(expectedEvent, event);
		}

		TEST_METHOD(Event3)
		{
			AddParser add;
			string event = add.extractEvent("meeting with boss on 10101");
			string expectedEvent = "";
			Assert::AreEqual(expectedEvent, event);
		}

		TEST_METHOD(Event4)
		{
			AddParser add;
			string event = add.extractEvent("meeting with boss on 1010124");
			string expectedEvent = "";
			Assert::AreEqual(expectedEvent, event);
		}

		TEST_METHOD(Event5)
		{
			AddParser add;
			string event = add.extractEvent("meeting with boss on 101014 on ");
			string expectedEvent = "";
			Assert::AreEqual(expectedEvent, event);
		}

		TEST_METHOD(Event6)
		{
			AddParser add;
			string event = add.extractEvent("on 101014 at 1700");
			string expectedEvent = "";
			Assert::AreEqual(expectedEvent, event);
		}

		TEST_METHOD(Event7)
		{
			AddParser add;
			string event = add.extractEvent("  on 101014 at 1700");
			string expectedEvent = "";
			Assert::AreEqual(expectedEvent, event);
		}

		TEST_METHOD(Date1)
		{
			AddParser add;
			ParsedDataPackage parsedData = add.parseNLandReturn("meeting with boss on 101014 at 1700");
			string expectedDate = "10/10/2014";
			Assert::AreEqual(expectedDate, parsedData.date);
		}

		TEST_METHOD(Date2)
		{
			AddParser add;
			ParsedDataPackage parsedData = add.parseNLandReturn("on 101014 at 1700");
			string expectedDate = "";
			Assert::AreEqual(expectedDate, parsedData.date);
		}

		TEST_METHOD(Time1)
		{
			AddParser add;
			ParsedDataPackage parsedData = add.parseNLandReturn("meeting with boss on 101214 at 1700");
			string expectedEndTime = "17:00";
			Assert::AreEqual(expectedEndTime, parsedData.end);
		}

		TEST_METHOD(Time2a)
		{
			AddParser add;
			ParsedDataPackage parsedData = add.parseNLandReturn("watch a midnight movie on 031214 from 1700 to 1800");
			string expectedStartTime = "17:00";
			Assert::AreEqual(expectedStartTime, parsedData.start);
		}

		TEST_METHOD(Time2b)
		{
			AddParser add;
			ParsedDataPackage parsedData = add.parseNLandReturn("watch a midnight movie on 031214 from 1700 to 1800");
			string expectedEndTime = "18:00";
			Assert::AreEqual(expectedEndTime, parsedData.end);
		}

		TEST_METHOD(Time3a)
		{
			AddParser add;
			ParsedDataPackage parsedData = add.parseNLandReturn("on 101014 from 1700 to 1800");
			string expectedStartTime = "";
			Assert::AreEqual(expectedStartTime, parsedData.start);
		}

		TEST_METHOD(Time3b)
		{
			AddParser add;
			ParsedDataPackage parsedData = add.parseNLandReturn("on 101014 from 1700 to 1800");
			string expectedEndTime = "";
			Assert::AreEqual(expectedEndTime, parsedData.end);
		}

		TEST_METHOD(Time4a)
		{
			AddParser add;
			ParsedDataPackage parsedData = add.parseNLandReturn("from 1700 to 1800");
			string expectedStartTime = "";
			Assert::AreEqual(expectedStartTime, parsedData.start);
		}

		TEST_METHOD(Time4b)
		{
			AddParser add;
			ParsedDataPackage parsedData = add.parseNLandReturn("from 1700 to 1800");
			string expectedEndTime = "";
			Assert::AreEqual(expectedEndTime, parsedData.end);
		}
	
		TEST_METHOD(Time5)
		{
			AddParser add;
			ParsedDataPackage parsedData = add.parseNLandReturn("meeting with boss on 101014 at 17000");
			string expectedEndTime = "";
			Assert::AreEqual(expectedEndTime, parsedData.end);
		}

		TEST_METHOD(Time6a)
		{
			AddParser add;
			ParsedDataPackage parsedData = add.parseNLandReturn("meeting with boss on 101014 from 17000 to 1800");
			string expectedStartTime = "";
			Assert::AreEqual(expectedStartTime, parsedData.start);
		}

		TEST_METHOD(Time6b)
		{
			AddParser add;
			ParsedDataPackage parsedData = add.parseNLandReturn("meeting with boss on 101014 from 1700 to 18000");
			string expectedEndTime = "";
			Assert::AreEqual(expectedEndTime, parsedData.end);
		}

		TEST_METHOD(Time7)
		{
			AddParser add;
			ParsedDataPackage parsedData = add.parseNLandReturn("meeting with boss on 101014 from 1700 to 1800+1");
			string expectedEndTime = "18:00+1";
			Assert::AreEqual(expectedEndTime, parsedData.end);
		}

		TEST_METHOD(Category1)
		{
			AddParser add;
			ParsedDataPackage parsedData = add.parseNLandReturn("meeting with boss on 101014 from 1700 to 1800 @boss");
			string expectedCategory = "boss";
			Assert::AreEqual(expectedCategory, parsedData.category);
		}

		TEST_METHOD(Category2)
		{
			AddParser add;
			ParsedDataPackage parsedData = add.parseNLandReturn("meeting with boss on 101014 from 1700 to 1800 @@meeting");
			string expectedCategory = "meeting";
			Assert::AreEqual(expectedCategory, parsedData.category);
		}

		TEST_METHOD(Category3)
		{
			AddParser add;
			ParsedDataPackage parsedData = add.parseNLandReturn("meeting with boss on 101014 from 1700 to 1800 -meeting-");
			string expectedCategory = "";
			Assert::AreEqual(expectedCategory, parsedData.category);
		}

		TEST_METHOD(OverallTest1)
		{
			AddParser add;
			ParsedDataPackage parsedData = add.parseNLandReturn("meeting with boss on tuesday from 1700 to 1800 @meeting");
			string expectedEvent = "meeting with boss";
			string expectedDate = "04/11/2014";
			string expectedStartTime = "17:00";
			string expectedEndTime = "18:00";
			string expectedCategory = "meeting";
			Assert::AreEqual(expectedEvent, parsedData.name);
			Assert::AreEqual(expectedDate, parsedData.date);
			Assert::AreEqual(expectedStartTime, parsedData.start);
			Assert::AreEqual(expectedEndTime, parsedData.end);
			Assert::AreEqual(expectedCategory, parsedData.category);
		}

		TEST_METHOD(OverallTest2)
		{
			AddParser add;
			ParsedDataPackage parsedData = add.parseNLandReturn("meeting with boss on next wed from 1700 to 1800 @meeting");
			string expectedEvent = "meeting with boss";
			string expectedDate = "05/11/2014";
			string expectedStartTime = "17:00";
			string expectedEndTime = "18:00";
			string expectedCategory = "meeting";
			Assert::AreEqual(expectedEvent, parsedData.name);
			Assert::AreEqual(expectedDate, parsedData.date);
			Assert::AreEqual(expectedStartTime, parsedData.start);
			Assert::AreEqual(expectedEndTime, parsedData.end);
			Assert::AreEqual(expectedCategory, parsedData.category);
		}

		TEST_METHOD(OverallTest3)
		{
			AddParser add;
			ParsedDataPackage parsedData = add.parseNLandReturn("meeting with boss on wed from 1700 to 1800 @meeting");
			string expectedEvent = "meeting with boss";
			string expectedDate = "05/11/2014";
			string expectedStartTime = "17:00";
			string expectedEndTime = "18:00";
			string expectedCategory = "meeting";
			Assert::AreEqual(expectedEvent, parsedData.name);
			Assert::AreEqual(expectedDate, parsedData.date);
			Assert::AreEqual(expectedStartTime, parsedData.start);
			Assert::AreEqual(expectedEndTime, parsedData.end);
			Assert::AreEqual(expectedCategory, parsedData.category);
		}
	};
}