//@author A0116410Y
#include "stdafx.h"
#include "CppUnitTest.h"
#include "AddLogic.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace t091c_test
{
	TEST_CLASS(LogicTestAdd)
	{
	public:
		
		TEST_METHOD(ADD_TIMED)
		{
			vector<string> testVector;
			string expected1 = "<name>test1</name><date>05/11/2014</date><start>00:00</start><end>23:59</end><category>test2</category><complete>no</complete><type>timed</type>";
			map<string, string> test1;
			test1.insert(pair<string, string>(NAME_ATTRIBUTE, "test1"));
			test1.insert(pair<string, string>(DATE_ATTRIBUTE, "05/11/2014"));
			test1.insert(pair<string, string>(START_ATTRIBUTE, "00:00"));
			test1.insert(pair<string, string>(END_ATTRIBUTE, "23:59"));
			test1.insert(pair<string, string>(CATEGORY_ATTRIBUTE, "test2"));
			AddLogic tester(testVector);
			tester.execute(test1);
			Assert::AreEqual(tester.getLineEntry(), expected1);
		}
		TEST_METHOD(ADD_DEADLINE)
		{
			vector<string> testVector;
			string expected1 = "<name>test1</name><date>05/11/2014</date><start></start><end>13:00</end><category>test1</category><complete>no</complete><type>deadline</type>";
			map<string, string> test1;
			test1.insert(pair<string, string>(NAME_ATTRIBUTE, "test1"));
			test1.insert(pair<string, string>(DATE_ATTRIBUTE, "05/11/2014"));
			test1.insert(pair<string, string>(START_ATTRIBUTE, ""));
			test1.insert(pair<string, string>(END_ATTRIBUTE, "13:00"));
			test1.insert(pair<string, string>(CATEGORY_ATTRIBUTE, "test1"));
			AddLogic tester(testVector);
			tester.execute(test1);
			Assert::AreEqual(tester.getLineEntry(), expected1);
		}
		TEST_METHOD(ADD_DEADLINE_NO_TIME)
		{
			vector<string> testVector;
			string expected1 = "<name>test1</name><date>05/11/2014</date><start></start><end>23:59</end><category>test1</category><complete>no</complete><type>deadline</type>";
			map<string, string> test1;
			test1.insert(pair<string, string>(NAME_ATTRIBUTE, "test1"));
			test1.insert(pair<string, string>(DATE_ATTRIBUTE, "05/11/2014"));
			test1.insert(pair<string, string>(START_ATTRIBUTE, ""));
			test1.insert(pair<string, string>(END_ATTRIBUTE, ""));
			test1.insert(pair<string, string>(CATEGORY_ATTRIBUTE, "test1"));
			AddLogic tester(testVector);
			tester.execute(test1);
			Assert::AreEqual(tester.getLineEntry(), expected1);
		}
		TEST_METHOD(ADD_FLOAT)
		{
			vector<string> testVector;
			string expected1 = "<name>test1</name><date></date><start></start><end></end><category>test1</category><complete>no</complete><type>float</type>";
			map<string, string> test1;
			test1.insert(pair<string, string>(NAME_ATTRIBUTE, "test1"));
			test1.insert(pair<string, string>(DATE_ATTRIBUTE, ""));
			test1.insert(pair<string, string>(START_ATTRIBUTE, ""));
			test1.insert(pair<string, string>(END_ATTRIBUTE, ""));
			test1.insert(pair<string, string>(CATEGORY_ATTRIBUTE, "test1"));
			AddLogic tester(testVector);
			tester.execute(test1);
			Assert::AreEqual(tester.getLineEntry(), expected1);
		}
		TEST_METHOD(ADD_WRONG_TIME)
		{
			vector<string> testVector;
			map<string, string> test1;
			test1.insert(pair<string, string>(NAME_ATTRIBUTE, "test1"));
			test1.insert(pair<string, string>(DATE_ATTRIBUTE, "05/11/2014"));
			test1.insert(pair<string, string>(START_ATTRIBUTE, ""));
			test1.insert(pair<string, string>(END_ATTRIBUTE, "24:00"));
			test1.insert(pair<string, string>(CATEGORY_ATTRIBUTE, "test1"));
			AddLogic tester(testVector);
			try {
				tester.execute(test1);
				Assert::IsTrue(false);
			}
			catch (const exception& ex) {
				Assert::IsTrue(true && ex.what());
			}
			test1[END_ATTRIBUTE] = "23:60";
			try {
				tester.execute(test1);
				Assert::IsTrue(false);
			}
			catch (const exception& ex) {
				Assert::IsTrue(true && ex.what());
			}
		}
		TEST_METHOD(ADD_WRONG_DATE)
		{
			vector<string> testVector;
			map<string, string> test1;
			test1.insert(pair<string, string>(NAME_ATTRIBUTE, "test1"));
			test1.insert(pair<string, string>(DATE_ATTRIBUTE, "31/11/2014"));
			test1.insert(pair<string, string>(START_ATTRIBUTE, ""));
			test1.insert(pair<string, string>(END_ATTRIBUTE, ""));
			test1.insert(pair<string, string>(CATEGORY_ATTRIBUTE, "test1"));
			AddLogic tester(testVector);
			try {
				tester.execute(test1);
				Assert::IsTrue(false);
			}
			catch (const exception& ex) {
				Assert::IsTrue(true && ex.what());
			}
			test1[DATE_ATTRIBUTE] = "30/13/2014";
			try {
				tester.execute(test1);
				Assert::IsTrue(false);
			}
			catch (const exception& ex) {
				Assert::IsTrue(true && ex.what());
			}
		}
	};
}