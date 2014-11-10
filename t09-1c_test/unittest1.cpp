#include "stdafx.h"
#include "CppUnitTest.h"
#include "AddLogic.h"
#include "FileEntryFormatter.h"
#include "DL_Algorithm.h"
#include "ProgramController.h"
#include "SearchLogic.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace t091c_test
{		
	TEST_CLASS(FORMATTER_CHECK)
	{
	public:
		
		TEST_METHOD(FORMATTER_DELETE_DETERMINE_CHECK)
		{
			string entry = "<name>check</name><date>10/10/2014</date>";
			string output = FileEntryFormatter::deleteAttributedEntryFromLineEntry("date", entry);
			string expected = "<name>check</name>";
			Assert::AreEqual(output, expected);
			entry = "<name>check</name><date>10/10/2014</date>";
			output = FileEntryFormatter::deleteAttributedEntryFromLineEntry("name", entry);
			expected = "<date>10/10/2014</date>";
			Assert::AreEqual(output, expected);
		}
		TEST_METHOD(FORMATTER_EDIT_DETERMINE_CHECK)
		{
			string entry = "<name>check</name><date>10/10/2014</date>";
			string output = FileEntryFormatter::editAttributedEntryFromLineEntry("date", "10/11/2014", entry);
			string expected = "<name>check</name><date>10/11/2014</date>";
			Assert::AreEqual(output, expected);
			entry = "<name>check</name><date>10/10/2014</date>";
			output = FileEntryFormatter::editAttributedEntryFromLineEntry("name", "check2", entry);
			expected = "<name>check2</name><date>10/10/2014</date>";
			Assert::AreEqual(output, expected);
		}
		TEST_METHOD(FORMATTER_GET_DETERMINE_CHECK)
		{
			string entry = "<name>check</name><date>10/10/2014</date>";
			string output = FileEntryFormatter::getAttributeEntry("date", entry);
			string expected = "10/10/2014";
			Assert::AreEqual(output, expected);
			entry = "<name>check</name><date>10/10/2014</date>";
			output = FileEntryFormatter::getAttributeEntry("name", entry);
			expected = "check";
			Assert::AreEqual(output, expected);
		}

		TEST_METHOD(DAMERAU_DETERMINE_CHECK)
		{
			DL_Algorithm check;
			Assert::AreEqual(check.findDLCost("hello", "hell"), 5);
			Assert::AreEqual(check.findDLCost("hello", "hlel"), 10);
			Assert::AreEqual(check.findDLCost("hello", "good hellol"), 0);
			Assert::AreEqual(check.findDLCost("", "hell"), 0);
			Assert::AreEqual(check.findDLCost("god", "dog"), 8);
			Assert::AreEqual(check.findDLCost("190914", "19/09/2014"), 0);
			Assert::AreEqual(check.findDLCost("170914", "19/09/2014"), 4);
		}
	};
}