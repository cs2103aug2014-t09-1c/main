#include "stdafx.h"
#include "CppUnitTest.h"
#include "AddParser.h"
#include "ParsedDataPackage.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace t091c_test
{
	TEST_CLASS(UnitTestParserNL)
	{
	public:
		
		TEST_METHOD(ParserNLtest1)
		{
			AddParser add;
			ParsedDataPackage parsedData = add.parseNLandReturn("meeting with boss on 101014 at 1700");
			string expectedCategory = "";
			string expectedTime = "17:00";
			string expectedDate = "10/10/2014";
			string expectedName = "meeting with boss";
			Assert::AreEqual(expectedCategory, parsedData.category);
			Assert::AreEqual(expectedTime, parsedData.start);
			Assert::AreEqual(expectedDate, parsedData.date);
			Assert::AreEqual(expectedName, parsedData.name);
		}

		TEST_METHOD(TimeTest1)
		{
			AddParser add;
			ParsedDataPackage parsedData = add.parseNLandReturn("at 1700");
			string expectedCategory = "";
			string expectedTime = "17:00";
			string expectedDate = "";
			string expectedName = "";
			//Assert::AreEqual(expectedCategory, parsedData.category);
			Assert::AreEqual(expectedTime, parsedData.end);
			//Assert::AreEqual(expectedDate, parsedData.date);
			//Assert::AreEqual(expectedName, parsedData.name);
		}

		TEST_METHOD(DateTest1)
		{
			AddParser add;
			ParsedDataPackage parsedData = add.parseNLandReturn("on 101014");
			string expectedCategory = "";
			string expectedTime = "";
			string expectedDate = "10/10/2014";
			string expectedName = "";
			//Assert::AreEqual(expectedCategory, parsedData.category);
			//Assert::AreEqual(expectedTime, parsedData.end);
			Assert::AreEqual(expectedDate, parsedData.date);
			//Assert::AreEqual(expectedName, parsedData.name);
		}

		TEST_METHOD(CategoryTest1)
		{
			AddParser add;
			ParsedDataPackage parsedData = add.parseNLandReturn("meeting with boss \"boss\"");
			string expectedCategory = "boss";
			string expectedTime = "";
			string expectedDate = "";
			string expectedName = "";
			Assert::AreEqual(expectedCategory, parsedData.category);
			//Assert::AreEqual(expectedTime, parsedData.start);
			//Assert::AreEqual(expectedDate, parsedData.date);
			//Assert::AreEqual(expectedName, parsedData.name);
		}

		TEST_METHOD(NameTest1)
		{
			AddParser add;
			ParsedDataPackage parsedData = add.parseNLandReturn("meeting with boss");
			string expectedCategory = "";
			string expectedTime = "";
			string expectedDate = "";
			string expectedName = "meeting with boss";
			//Assert::AreEqual(expectedCategory, parsedData.category);
			//Assert::AreEqual(expectedTime, parsedData.start);
			//Assert::AreEqual(expectedDate, parsedData.date);
			Assert::AreEqual(expectedName, parsedData.name);
		}
	};
}