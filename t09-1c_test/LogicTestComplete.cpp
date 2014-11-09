#include "stdafx.h"
#include "CppUnitTest.h"
#include "CompleteLogic.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace t091c_test
{
	TEST_CLASS(LogicTestComplete)
	{
	public:
		
		TEST_METHOD(COMPLETE_ONE_ENTRY)
		{
			const vector<string> keywords;
			const int displayCase = 0;
			vector<string> testVector;
			testVector.push_back("<name>test1</name><date>05/11/2014</date><start></start><end>13:00</end><category>test1</category><complete>no</complete><type>deadline</type>");
			map<string, int> test1Pos;
			test1Pos.insert(pair<string, int>(FROM_POSITION, 1));
			test1Pos.insert(pair<string, int>(TO_POSITION, 1));
			CompleteLogic tester(testVector, "01/11/2014", keywords, displayCase);
			tester.execute(test1Pos, 1);
			string expected = "<name>test1</name><date>05/11/2014</date><start></start><end>13:00</end><category>test1</category><complete>yes</complete><type>deadline</type>";
			Assert::AreEqual(expected, tester.getEntriesVector()[0]);
		}
		TEST_METHOD(COMPLETE_MULTIPLE_ENTRIES)
		{
			const vector<string> keywords;
			const int displayCase = 0;
			vector<string> testVector;
			testVector.push_back("<name>test1</name><date>05/11/2014</date><start></start><end>13:00</end><category>test1</category><complete>no</complete><type>deadline</type>");
			testVector.push_back("<name>test2</name><date>05/11/2014</date><start>13:00</start><end>15:00</end><category>test2</category><complete>no</complete><type>timed</type>");
			map<string, int> test1Pos;
			test1Pos.insert(pair<string, int>(FROM_POSITION, 1));
			test1Pos.insert(pair<string, int>(TO_POSITION, 2));
			CompleteLogic tester(testVector, "01/11/2014", keywords, displayCase);
			tester.execute(test1Pos, 1);
			string expected1 = "<name>test1</name><date>05/11/2014</date><start></start><end>13:00</end><category>test1</category><complete>yes</complete><type>deadline</type>";
			string expected2 = "<name>test2</name><date>05/11/2014</date><start>13:00</start><end>15:00</end><category>test2</category><complete>yes</complete><type>timed</type>";
			Assert::AreEqual(expected1, tester.getEntriesVector()[0]);
			Assert::AreEqual(expected2, tester.getEntriesVector()[1]);
		}
		TEST_METHOD(COMPLETE_OUT_OF_BOUNDS)
		{
			const vector<string> keywords;
			const int displayCase = 0;
			vector<string> testVector;
			testVector.push_back("<name>test1</name><date>05/11/2014</date><start></start><end>13:00</end><category>test1</category><complete>no</complete><type>deadline</type>");
			testVector.push_back("<name>test2</name><date>05/11/2014</date><start>13:00</start><end>15:00</end><category>test2</category><complete>no</complete><type>timed</type>");
			map<string, int> test1Pos;
			test1Pos.insert(pair<string, int>(FROM_POSITION, 0));
			test1Pos.insert(pair<string, int>(TO_POSITION, 2));
			CompleteLogic tester(testVector, "01/11/2014", keywords, displayCase);
			try {
				tester.execute(test1Pos, 1);
				Assert::IsTrue(false);
			}
			catch (const exception& ex) {
				Assert::IsTrue(true && ex.what());
			}
			test1Pos[FROM_POSITION] = 1;
			test1Pos[TO_POSITION] = 3;
			try {
				tester.execute(test1Pos, 1);
				Assert::IsTrue(false);
			}
			catch (const exception& ex) {
				Assert::IsTrue(true && ex.what());
			}
		}

	};
}