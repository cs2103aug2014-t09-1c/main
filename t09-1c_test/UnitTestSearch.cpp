#include "stdafx.h"
#include "CppUnitTest.h"
#include "SearchParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace t091c_test
{
	TEST_CLASS(UnitTest2)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			SearchParser test;
			string argument = test.findTypeAndGetArgument("date 111014");
			string expectedArgument = "111014";
			Assert::AreEqual(expectedArgument,argument);
		}
		TEST_METHOD(TestMethod2)
		{
			SearchParser test;
			string argument = test.findTypeAndGetArgument("date 1110141");
			test.extractDate(argument);
			string errorString = SEARCH_PARSER_6DIGIT_DATE_ERROR;
			Assert::AreEqual(errorString, test.getErrorString());
		}
		TEST_METHOD(TestMethod3)
		{
			SearchParser test;
			string argument = test.findTypeAndGetArgument("date 111014  ");
			string date = test.extractDate(argument);
			string testDate = "11/10/14";
			Assert::AreEqual(testDate, date);
		}
		/*ParsedDataPackage SearchParser::parseAndReturn(string parseInput)
		{
			string argument = findTypeAndGetArgument(parseInput);
			if (type == "date"){
				parsedData.date = extractDate(argument);
			}
			else if (type == "name"){
				parsedData.name = argument;
			}
			else if (type == "category"){
				parsedData.category = argument;
			}
			return parsedData;
		}*/
	};
}