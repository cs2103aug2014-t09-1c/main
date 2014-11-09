#include "stdafx.h"
#include "CppUnitTest.h"
#include "DeleteLogic.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace t091c_test
{
	TEST_CLASS(LogicTestDelete)
	{
	public:
		
		TEST_METHOD(DELETE_ONE_ENTRY)
		{
			const vector<string> keywords;
			const int displayCase = 0;
			vector<string> testVector;
			testVector.push_back("<name>test1</name><date>05/11/2014</date><start></start><end>13:00</end><category>test1</category><complete>no</complete><type>deadline</type>");
			map<string, int> test1Pos;
			test1Pos.insert(pair<string, int>(FROM_POSITION, 1));
			test1Pos.insert(pair<string, int>(TO_POSITION, 1));
			DeleteLogic tester(testVector, "01/11/2014", keywords, displayCase);
			tester.execute(test1Pos);
			Assert::IsTrue(tester.getEntriesVector().size() == 0);
		}
		TEST_METHOD(DELETE_ONE_ENTRY_OUT_OF_BOUNDS)
		{
			const vector<string> keywords;
			const int displayCase = 0;
			vector<string> testVector;
			testVector.push_back("<name>test1</name><date>05/11/2014</date><start></start><end>13:00</end><category>test1</category><complete>no</complete><type>deadline</type>");
			testVector.push_back("<name>test2</name><date>05/11/2014</date><start>13:00</start><end>15:00</end><category>test2</category><complete>no</complete><type>timed</type>");
			testVector.push_back("<name>test3</name><date>05/11/2014</date><start></start><end>23:59</end><category>test3</category><complete>no</complete><type>deadline</type>");
			testVector.push_back("<name>test4</name><date></date><start></start><end></end><category>test4</category><complete>no</complete><type>float</type>");
			map<string, int> test1Pos;
			test1Pos.insert(pair<string, int>(FROM_POSITION, 0));
			test1Pos.insert(pair<string, int>(TO_POSITION, 0));
			DeleteLogic tester(testVector, "01/11/2014", keywords, displayCase);
			try {
				tester.execute(test1Pos);
				Assert::IsTrue(false);
			}
			catch (const exception& ex) {
				Assert::IsTrue(true && ex.what());
			}
			test1Pos[TO_POSITION] = 5;
			try {
				tester.execute(test1Pos);
				Assert::IsTrue(false);
			}
			catch (const exception& ex) {
				Assert::IsTrue(true && ex.what());
			}
		}
		TEST_METHOD(DELETE_MULTIPLE_ENTRIES)
		{
			const vector<string> keywords;
			const int displayCase = 0;
			vector<string> testVector;
			testVector.push_back("<name>test1</name><date>05/11/2014</date><start></start><end>13:00</end><category>test1</category><complete>no</complete><type>deadline</type>");
			testVector.push_back("<name>test2</name><date>05/11/2014</date><start>13:00</start><end>15:00</end><category>test2</category><complete>no</complete><type>timed</type>");
			testVector.push_back("<name>test3</name><date>05/11/2014</date><start></start><end>23:59</end><category>test3</category><complete>no</complete><type>deadline</type>");
			testVector.push_back("<name>test4</name><date></date><start></start><end></end><category>test4</category><complete>no</complete><type>float</type>");
			map<string, int> test1Pos;
			test1Pos.insert(pair<string, int>(FROM_POSITION, 1));
			test1Pos.insert(pair<string, int>(TO_POSITION, 4));
			DeleteLogic tester(testVector, "01/11/2014", keywords, displayCase);
			tester.execute(test1Pos);
			Assert::IsTrue(tester.getEntriesVector().size() == 0);
		}
		TEST_METHOD(DELETE_MULTIPLE_ENTRIES_OUT_OF_BOUNDS)
		{
			const vector<string> keywords;
			const int displayCase = 0;
			vector<string> testVector;
			testVector.push_back("<name>test1</name><date>05/11/2014</date><start></start><end>13:00</end><category>test1</category><complete>no</complete><type>deadline</type>");
			testVector.push_back("<name>test2</name><date>05/11/2014</date><start>13:00</start><end>15:00</end><category>test2</category><complete>no</complete><type>timed</type>");
			testVector.push_back("<name>test3</name><date>05/11/2014</date><start></start><end>23:59</end><category>test3</category><complete>no</complete><type>deadline</type>");
			testVector.push_back("<name>test4</name><date></date><start></start><end></end><category>test4</category><complete>no</complete><type>float</type>");
			map<string, int> test1Pos;
			test1Pos.insert(pair<string, int>(FROM_POSITION, 0));
			test1Pos.insert(pair<string, int>(TO_POSITION, 4));
			DeleteLogic tester(testVector, "01/11/2014", keywords, displayCase);
			try {
				tester.execute(test1Pos);
				Assert::IsTrue(false);
			}
			catch (const exception& ex) {
				Assert::IsTrue(true && ex.what());
			}
			test1Pos[FROM_POSITION] = 1;
			test1Pos[TO_POSITION] = 5;
			try {
				tester.execute(test1Pos);
				Assert::IsTrue(false);
			}
			catch (const exception& ex) {
				Assert::IsTrue(true && ex.what());
			}
		}
	};
}