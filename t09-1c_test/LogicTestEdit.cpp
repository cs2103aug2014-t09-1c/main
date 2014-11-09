#include "stdafx.h"
#include "CppUnitTest.h"
#include "EditLogic.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace t091c_test
{
	TEST_CLASS(LogicTestEdit)
	{
	public:

		TEST_METHOD(EDIT_CONTENT_CHANGE)
		{
			const vector<string> keywords;
			const int displayCase = 0;
			vector<string> testVector;
			testVector.push_back("<name>test1</name><date>01/11/2014</date><start>00:00</start><end>23:59</end><category>test2</category><complete>no</complete><type>timed</type>");
			string expected1 = "<name>test1</name><date>05/11/2014</date><start>13:00</start><end>15:00</end><category>test2</category><complete>no</complete><type>timed</type>";
			map<string, string> test1;
			map<string, int> test1Pos;
			test1.insert(pair<string, string>(NAME_ATTRIBUTE, "test1"));
			test1.insert(pair<string, string>(DATE_ATTRIBUTE, "05/11/2014"));
			test1.insert(pair<string, string>(START_ATTRIBUTE, "13:00"));
			test1.insert(pair<string, string>(END_ATTRIBUTE, "15:00"));
			test1.insert(pair<string, string>(CATEGORY_ATTRIBUTE, "test2"));
			test1Pos.insert(pair<string, int>(FROM_POSITION, 1));
			EditLogic tester(testVector,"01/11/2015", keywords, displayCase);
			tester.execute(test1Pos, test1);
			Assert::AreEqual(tester.getEntriesVector()[0], expected1);
		}
		TEST_METHOD(EDIT_CONTENT_TYPE_CHANGE)
		{
			const vector<string> keywords;
			const int displayCase = 0;
			vector<string> testVector;
			testVector.push_back("<name>test1</name><date>01/11/2014</date><start></start><end>23:59</end><category>test2</category><complete>no</complete><type>deadline</type>");
			string expected1 = "<name>test1</name><date>05/11/2014</date><start>13:00</start><end>15:00</end><category>test2</category><complete>no</complete><type>timed</type>";
			map<string, string> test1;
			map<string, int> test1Pos;
			test1.insert(pair<string, string>(NAME_ATTRIBUTE, "test1"));
			test1.insert(pair<string, string>(DATE_ATTRIBUTE, "05/11/2014"));
			test1.insert(pair<string, string>(START_ATTRIBUTE, "13:00"));
			test1.insert(pair<string, string>(END_ATTRIBUTE, "15:00"));
			test1.insert(pair<string, string>(CATEGORY_ATTRIBUTE, "test2"));
			test1Pos.insert(pair<string, int>(FROM_POSITION, 1));
			EditLogic tester(testVector, "01/11/2015", keywords, displayCase);
			tester.execute(test1Pos, test1);
			Assert::AreEqual(tester.getEntriesVector()[0], expected1);
		}
		TEST_METHOD(EDIT_CONTENT_OUT_OF_BOUNDS)
		{
			const vector<string> keywords;
			const int displayCase = 0;
			vector<string> testVector;
			testVector.push_back("<name>test1</name><date>01/11/2014</date><start></start><end>23:59</end><category>test2</category><complete>no</complete><type>deadline</type>");
			map<string, string> test1;
			map<string, int> test1Pos;
			test1.insert(pair<string, string>(NAME_ATTRIBUTE, "test1"));
			test1.insert(pair<string, string>(DATE_ATTRIBUTE, "05/11/2014"));
			test1.insert(pair<string, string>(START_ATTRIBUTE, "13:00"));
			test1.insert(pair<string, string>(END_ATTRIBUTE, "15:00"));
			test1.insert(pair<string, string>(CATEGORY_ATTRIBUTE, "test2"));
			test1Pos.insert(pair<string, int>(FROM_POSITION, 0));
			EditLogic tester(testVector, "01/11/2015", keywords, displayCase);
			try {
				tester.execute(test1Pos, test1);
				Assert::IsTrue(false);
			}
			catch (const exception& ex) {
				Assert::IsTrue(true && ex.what());
			}
			test1Pos[FROM_POSITION] = 2;
			try {
				tester.execute(test1Pos, test1);
				Assert::IsTrue(false);
			}
			catch (const exception& ex) {
				Assert::IsTrue(true && ex.what());
			}
		}
		TEST_METHOD(EDIT_CONTENT_WRONG_DATE)
		{
			const vector<string> keywords;
			const int displayCase = 0;
			vector<string> testVector;
			testVector.push_back("<name>test1</name><date>01/11/2014</date><start></start><end>23:59</end><category>test2</category><complete>no</complete><type>deadline</type>");
			map<string, string> test1;
			map<string, int> test1Pos;
			test1.insert(pair<string, string>(NAME_ATTRIBUTE, "test1"));
			test1.insert(pair<string, string>(DATE_ATTRIBUTE, "31/11/2014"));
			test1.insert(pair<string, string>(START_ATTRIBUTE, "13:00"));
			test1.insert(pair<string, string>(END_ATTRIBUTE, "15:00"));
			test1.insert(pair<string, string>(CATEGORY_ATTRIBUTE, "test2"));
			test1Pos.insert(pair<string, int>(FROM_POSITION, 1));
			EditLogic tester(testVector, "01/11/2014", keywords, displayCase);
			try {
				tester.execute(test1Pos, test1);
				Assert::IsTrue(false);
			}
			catch (const exception& ex) {
				Assert::IsTrue(true && ex.what());
			}
			test1[DATE_ATTRIBUTE] = "01/13/2014";
			try {
				tester.execute(test1Pos, test1);
				Assert::IsTrue(false);
			}
			catch (const exception& ex) {
				Assert::IsTrue(true && ex.what());
			}
		}
		TEST_METHOD(EDIT_CONTENT_WRONG_TIME)
		{
			const vector<string> keywords;
			const int displayCase = 0;
			vector<string> testVector;
			testVector.push_back("<name>test1</name><date>01/11/2014</date><start></start><end>23:59</end><category>test2</category><complete>no</complete><type>deadline</type>");
			map<string, string> test1;
			map<string, int> test1Pos;
			test1.insert(pair<string, string>(NAME_ATTRIBUTE, "test1"));
			test1.insert(pair<string, string>(DATE_ATTRIBUTE, "30/11/2014"));
			test1.insert(pair<string, string>(START_ATTRIBUTE, ""));
			test1.insert(pair<string, string>(END_ATTRIBUTE, "24:00"));
			test1.insert(pair<string, string>(CATEGORY_ATTRIBUTE, "test2"));
			test1Pos.insert(pair<string, int>(FROM_POSITION, 1));
			EditLogic tester(testVector, "01/11/2014", keywords, displayCase);
			try {
				tester.execute(test1Pos, test1);
				Assert::IsTrue(false);
			}
			catch (const exception& ex) {
				Assert::IsTrue(true && ex.what());
			}
			test1[END_ATTRIBUTE] = "23:60";
			try {
				tester.execute(test1Pos, test1);
				Assert::IsTrue(false);
			}
			catch (const exception& ex) {
				Assert::IsTrue(true && ex.what());
			}
		}
	};
}