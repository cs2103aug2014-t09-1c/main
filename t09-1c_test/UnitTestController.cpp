#include "stdafx.h"
#include "CppUnitTest.h"
#include "SearchParser.h"
#include "TimeParser.h"
#include "ProgramController.h"
#include "ParsedDataDeployer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace t091c_test
{
	TEST_CLASS(UnitTestController)
	{
	public:
		

		TEST_METHOD(INTEGRATED_TESTING_ADD)
		{
			vector<string> testVector;
			ProgramController test(testVector);
			test.executeEntry("add [test1][051114][1300][test1]");
			string testString1 = "<name>test1</name><date>05/11/2014</date><start></start><end>13:00</end><category>test1</category><complete>no</complete><type>deadline</type>";
			Assert::AreEqual(testString1, test.returnTestVector()[0]);

			test.executeEntry("add [test2][051114][1300-1500][test2]");
			string testString2 = "<name>test2</name><date>05/11/2014</date><start>13:00</start><end>15:00</end><category>test2</category><complete>no</complete><type>timed</type>";
			Assert::AreEqual(testString2, test.returnTestVector()[1]);

			test.executeEntry("add [test3][051114][][test3]");
			string testString3 = "<name>test3</name><date>05/11/2014</date><start></start><end>23:59</end><category>test3</category><complete>no</complete><type>deadline</type>";
			Assert::AreEqual(testString3, test.returnTestVector()[2]);

			test.executeEntry("add [test4][][][test4]");
			string testString4 = "<name>test4</name><date></date><start></start><end></end><category>test4</category><complete>no</complete><type>float</type>";
			Assert::AreEqual(testString4, test.returnTestVector()[3]);

			test.executeEntry("add [test4][xxx][xxx][test4]");
			size_t vectorSizeTest5 = 4;
			Assert::AreEqual(vectorSizeTest5, test.returnTestVector().size());
		}
		TEST_METHOD(INTEGRATED_TESTING_EDIT)//to show different ways of editing
		{
			vector<string> testVector;
			testVector.push_back("<name>test1</name><date>05/11/2014</date><start></start><end>13:00</end><category>test1</category><complete>no</complete><type>deadline</type>");
			testVector.push_back("<name>test2</name><date>05/11/2014</date><start>13:00</start><end>15:00</end><category>test2</category><complete>no</complete><type>timed</type>");
			testVector.push_back("<name>test3</name><date>05/11/2014</date><start></start><end>23:59</end><category>test3</category><complete>no</complete><type>deadline</type>");
			testVector.push_back("<name>test4</name><date></date><start></start><end></end><category>test4</category><complete>no</complete><type>float</type>");
			
			ProgramController test(testVector); //edit time
			test.executeEntry("edit 1 [test1][051114][1100][test1]");
			string testString1 = "<name>test1</name><date>05/11/2014</date><start></start><end>11:00</end><category>test1</category><complete>no</complete><type>deadline</type>";
			Assert::AreEqual(testString1, test.returnTestVector()[0]);

			test.executeEntry("edit 2 [test2][051114][1500][test2]");// edit deadline to timed
			string testString2 = "<name>test2</name><date>05/11/2014</date><start></start><end>15:00</end><category>test2</category><complete>no</complete><type>deadline</type>";
			Assert::AreEqual(testString2, test.returnTestVector()[1]);

			test.executeEntry("edit 3 [test2][051114][1500-1700][test2]");//edit name, category and deadline to timed
			string testString3 = "<name>test2</name><date>05/11/2014</date><start>15:00</start><end>17:00</end><category>test2</category><complete>no</complete><type>timed</type>";
			Assert::AreEqual(testString3, test.returnTestVector()[2]);
		}
		TEST_METHOD(INTEGRATED_TESTING_DELETE)//to show basic case that delete single line is working, and borderline cases where delete range exceeds task number range
		{
			vector<string> testVector;
			testVector.push_back("<name>test1</name><date>05/11/2014</date><start></start><end>13:00</end><category>test1</category><complete>no</complete><type>deadline</type>");
			testVector.push_back("<name>test2</name><date>05/11/2014</date><start>13:00</start><end>15:00</end><category>test2</category><complete>no</complete><type>timed</type>");
			testVector.push_back("<name>test3</name><date>05/11/2014</date><start></start><end>23:59</end><category>test3</category><complete>no</complete><type>deadline</type>");
			testVector.push_back("<name>test4</name><date></date><start></start><end></end><category>test4</category><complete>no</complete><type>float</type>");

			ProgramController test(testVector);
			test.executeEntry("all");
			test.executeEntry("delete 1");
			size_t vectorSizeTest5 = 3;
			Assert::AreEqual(vectorSizeTest5, test.returnTestVector().size());
			test.executeEntry("delete 1 to 4");
			size_t vectorSizeTest6 = 3;
			Assert::AreEqual(vectorSizeTest6, test.returnTestVector().size());
			test.executeEntry("delete 0 to 3");
			size_t vectorSizeTest7 = 3;
			Assert::AreEqual(vectorSizeTest7, test.returnTestVector().size());
			test.executeEntry("delete 1 to 3");
			size_t vectorSizeTest8 = 0;
			Assert::AreEqual(vectorSizeTest8, test.returnTestVector().size());
		}
		TEST_METHOD(INTEGRATED_TESTING_COMPLETE)
		{
			vector<string> testVector;
			testVector.push_back("<name>test1</name><date>05/11/2014</date><start></start><end>13:00</end><category>test1</category><complete>no</complete><type>deadline</type>");
			testVector.push_back("<name>test2</name><date>05/11/2014</date><start>13:00</start><end>15:00</end><category>test2</category><complete>no</complete><type>timed</type>");
			testVector.push_back("<name>test3</name><date>05/11/2014</date><start></start><end>23:59</end><category>test3</category><complete>no</complete><type>deadline</type>");
			testVector.push_back("<name>test4</name><date></date><start></start><end></end><category>test4</category><complete>no</complete><type>float</type>");

			ProgramController test(testVector);//test for single complete, mass complete and boundary cases
			test.executeEntry("all");
			test.executeEntry("complete 1");
			string expected1 = "<name>test1</name><date>05/11/2014</date><start></start><end>13:00</end><category>test1</category><complete>yes</complete><type>deadline</type>";
			Assert::AreEqual(expected1, test.returnTestVector()[0]);
			test.executeEntry("complete 1 to 5");
			Assert::AreEqual(testVector[1], test.returnTestVector()[1]);
			Assert::AreEqual(testVector[2], test.returnTestVector()[2]);
			Assert::AreEqual(testVector[3], test.returnTestVector()[3]);
			test.executeEntry("complete 0 to 3");
			Assert::AreEqual(testVector[1], test.returnTestVector()[1]);
			Assert::AreEqual(testVector[2], test.returnTestVector()[2]);
			Assert::AreEqual(testVector[3], test.returnTestVector()[3]);
			test.executeEntry("complete 1 to 4");
			string expected2 = "<name>test2</name><date>05/11/2014</date><start>13:00</start><end>15:00</end><category>test2</category><complete>yes</complete><type>timed</type>";
			string expected3 = "<name>test3</name><date>05/11/2014</date><start></start><end>23:59</end><category>test3</category><complete>yes</complete><type>deadline</type>";
			string expected4 = "<name>test4</name><date></date><start></start><end></end><category>test4</category><complete>yes</complete><type>float</type>";
			Assert::AreEqual(expected2, test.returnTestVector()[1]);
			Assert::AreEqual(expected3, test.returnTestVector()[2]);
			Assert::AreEqual(expected4, test.returnTestVector()[3]);
		}
		TEST_METHOD(INTEGRATED_TESTING_UNCOMPLETE)//test for single uncomplete, mass uncomplete and boundary cases
		{
			vector<string> testVector;
			testVector.push_back("<name>test1</name><date>05/11/2014</date><start></start><end>13:00</end><category>test1</category><complete>yes</complete><type>deadline</type>");
			testVector.push_back("<name>test2</name><date>05/11/2014</date><start>13:00</start><end>15:00</end><category>test2</category><complete>yes</complete><type>timed</type>");
			testVector.push_back("<name>test3</name><date>05/11/2014</date><start></start><end>23:59</end><category>test3</category><complete>yes</complete><type>deadline</type>");
			testVector.push_back("<name>test4</name><date></date><start></start><end></end><category>test4</category><complete>yes</complete><type>float</type>");

			ProgramController test(testVector);
			test.executeEntry("all");
			test.executeEntry("uncomplete 1");
			string expected1 = "<name>test1</name><date>05/11/2014</date><start></start><end>13:00</end><category>test1</category><complete>no</complete><type>deadline</type>";
			Assert::AreEqual(expected1, test.returnTestVector()[0]);
			test.executeEntry("uncomplete 1 to 5");
			Assert::AreEqual(testVector[1], test.returnTestVector()[1]);
			Assert::AreEqual(testVector[2], test.returnTestVector()[2]);
			Assert::AreEqual(testVector[3], test.returnTestVector()[3]);
			test.executeEntry("uncomplete 0 to 3");
			Assert::AreEqual(testVector[1], test.returnTestVector()[1]);
			Assert::AreEqual(testVector[2], test.returnTestVector()[2]);
			Assert::AreEqual(testVector[3], test.returnTestVector()[3]);
			test.executeEntry("uncomplete 1 to 4");
			string expected2 = "<name>test2</name><date>05/11/2014</date><start>13:00</start><end>15:00</end><category>test2</category><complete>no</complete><type>timed</type>";
			string expected3 = "<name>test3</name><date>05/11/2014</date><start></start><end>23:59</end><category>test3</category><complete>no</complete><type>deadline</type>";
			string expected4 = "<name>test4</name><date></date><start></start><end></end><category>test4</category><complete>no</complete><type>float</type>";
			Assert::AreEqual(expected2, test.returnTestVector()[1]);
			Assert::AreEqual(expected3, test.returnTestVector()[2]);
			Assert::AreEqual(expected4, test.returnTestVector()[3]);
		}
		TEST_METHOD(INTEGRATED_TESTING_CLIP)
		{
			vector<string> testVector;
			testVector.push_back("<name>test1</name><date>05/11/2014</date><start></start><end>13:00</end><category>test1</category><complete>yes</complete><type>deadline</type>");
			testVector.push_back("<name>test2</name><date>05/11/2014</date><start>13:00</start><end>15:00</end><category>test2</category><complete>yes</complete><type>timed</type>");
			testVector.push_back("<name>test3</name><date>05/11/2014</date><start></start><end>23:59</end><category>test3</category><complete>yes</complete><type>deadline</type>");
			testVector.push_back("<name>test4</name><date></date><start></start><end></end><category>test4</category><complete>yes</complete><type>float</type>");
			ProgramController test(testVector);
			test.executeEntry("all");
			string lineText1 = test.updateLineText("clip 1", true);
			string expected1 = "add [test1][051114][1300][test1]";
			Assert::AreEqual(expected1, lineText1);
			string lineText2 = test.updateLineText("clip 4", true);
			string expected2 = "add [test4][][][test4]";
			Assert::AreEqual(expected2, lineText2);
			string lineText3 = test.updateLineText("clip 0", true);
			string expected3 = "";
			Assert::AreEqual(expected3, lineText3);
			string lineText4 = test.updateLineText("clip 5", true);
			string expected4 = "";
			Assert::AreEqual(expected4, lineText4);
		}
		TEST_METHOD(INTEGRATED_TESTING_SEARCH)//filter valid search results
		{
			vector<string> testVector;
			testVector.push_back("<name>test1</name><date>05/11/2014</date><start></start><end>13:00</end><category>test1</category><complete>yes</complete><type>deadline</type>");
			testVector.push_back("<name>test2</name><date>05/11/2014</date><start>13:00</start><end>15:00</end><category>test2</category><complete>yes</complete><type>timed</type>");
			testVector.push_back("<name>test3</name><date>05/11/2014</date><start></start><end>23:59</end><category>test3</category><complete>yes</complete><type>deadline</type>");
			testVector.push_back("<name>test4</name><date></date><start></start><end></end><category>test4</category><complete>yes</complete><type>float</type>");
			ProgramController test(testVector);
			vector<string> vector1 = test.populateSuggestionBox("search test");
			Assert::IsTrue(vector1.size() == 4);
			vector<string> vector2 = test.populateSuggestionBox("search xxxxxxx");
			Assert::IsTrue(vector2.size() == 0);
			vector<string> vector3 = test.populateSuggestionBox("search 051114");
			Assert::IsTrue(vector3.size() == 1);
			Assert::IsTrue(vector3[0] == "05/11/2014");
			vector<string> vector4 = test.populateSuggestionBox("search 061114");
			Assert::IsTrue(vector4.size() == 0);
			vector<string> vector5 = test.populateSuggestionBox("search 1300");
			Assert::IsTrue(vector5.size() == 1);
			Assert::IsTrue(vector5[0] == "13:00");
			vector<string> vector6 = test.populateSuggestionBox("search 1301");
			Assert::IsTrue(vector6.size() == 1);
			Assert::IsTrue(vector6[0] == "13:01");
			vector<string> vector7 = test.populateSuggestionBox("search 1259");
			Assert::IsTrue(vector7.size() == 0);
		}
		TEST_METHOD(INTEGRATED_TESTING_SLOT)
		{
			vector<string> testVector;
			testVector.push_back("<name>test1</name><date>05/11/2014</date><start></start><end>13:00</end><category>test1</category><complete>yes</complete><type>deadline</type>");
			testVector.push_back("<name>test2</name><date>05/11/2014</date><start>13:00</start><end>15:00</end><category>test2</category><complete>yes</complete><type>timed</type>");
			testVector.push_back("<name>test3</name><date>05/11/2014</date><start></start><end>23:59</end><category>test3</category><complete>yes</complete><type>deadline</type>");
			testVector.push_back("<name>test4</name><date></date><start></start><end></end><category>test4</category><complete>yes</complete><type>float</type>");
			ProgramController test(testVector);
			string lineText1 = test.updateLineText("slot [051114][1500-1700][0200]", true);
			string expected1 = "add [][051114][1500-1700][]";
			Assert::AreEqual(expected1, lineText1);
			string lineText2 = test.updateLineText("slot [051114][1459-1700][0200]", true);
			string expected2 = "add [][051114][1500-1700][]";
			Assert::AreEqual(expected2, lineText2);
			string lineText3 = test.updateLineText("slot [051114][1300-1500][0200]", true);
			string expected3 = "";
			Assert::AreEqual(expected3, lineText3);
			string lineText4 = test.updateLineText("slot [051114][1100-1300][0200]", true);
			string expected4 = "add [][051114][1100-1300][]";
			Assert::AreEqual(expected4, lineText4);
			string lineText5 = test.updateLineText("slot [051114][1200-1600][0200]", true);
			string expected5 = "";
			Assert::AreEqual(expected5, lineText5);
			string lineText6 = test.updateLineText("slot [051114][1200-1700][0200]", true);
			string expected6 = "add [][051114][1500-1700][]";
			Assert::AreEqual(expected6, lineText6);
			string lineText7 = test.updateLineText("slot [051114][1501-1700][0200]", true);//boundary case
			string expected7 = "";
			Assert::AreEqual(expected7, lineText7);
			string lineText8 = test.updateLineText("slot [051114][1500-1501][0001]", true);//boundary case
			string expected8 = "add [][051114][1500-1501][]";
			Assert::AreEqual(expected8, lineText8);
			string lineText9 = test.updateLineText("slot [051114][1700-1500][0200]", true);//flipped
			string expected9 = "";
			Assert::AreEqual(expected9, lineText9);
			string lineText10 = test.updateLineText("slot [051114][0000-2359][1300]", true);//boundary case
			string expected10 = "add [][051114][0000-1300][]";
			Assert::AreEqual(expected10, lineText10);
			string lineText11 = test.updateLineText("slot [051114][0000-2359][2359]", true);//boundary case
			string expected11 = "";
			Assert::AreEqual(expected11, lineText11);

		}
		TEST_METHOD(INTEGRATED_TESTING_DISPLAY_ALL_COMPLETED)
		{
			vector<string> testVector;
			testVector.push_back("<name>test1</name><date>05/11/2014</date><start></start><end>13:00</end><category>test1</category><complete>yes</complete><type>deadline</type>");
			testVector.push_back("<name>test2</name><date>05/11/2014</date><start>13:00</start><end>15:00</end><category>test2</category><complete>yes</complete><type>timed</type>");
			testVector.push_back("<name>test3</name><date>05/11/2014</date><start></start><end>23:59</end><category>test3</category><complete>yes</complete><type>deadline</type>");
			testVector.push_back("<name>test4</name><date></date><start></start><end></end><category>test4</category><complete>yes</complete><type>float</type>");
			ProgramController test(testVector);
			vector<vector<string>> display1 = test.displayTable("05/11/2014");
			size_t expected1 = 3;
			Assert::AreEqual(display1.size(), expected1);
			vector<vector<string>> display2 = test.displayTable("06/11/2014");
			size_t expected2 = 0;
			Assert::AreEqual(display2.size(), expected2);
		}
		TEST_METHOD(INTEGRATED_TESTING_DISPLAY_NONE_COMPLETED)
		{
			vector<string> testVector;
			testVector.push_back("<name>test1</name><date>05/11/2014</date><start></start><end>13:00</end><category>test1</category><complete>no</complete><type>deadline</type>");
			testVector.push_back("<name>test2</name><date>05/11/2014</date><start>13:00</start><end>15:00</end><category>test2</category><complete>no</complete><type>timed</type>");
			testVector.push_back("<name>test3</name><date>05/11/2014</date><start></start><end>23:59</end><category>test3</category><complete>no</complete><type>deadline</type>");
			testVector.push_back("<name>test4</name><date></date><start></start><end></end><category>test4</category><complete>no</complete><type>float</type>");
			ProgramController test(testVector);
			vector<vector<string>> display1 = test.displayTable("05/11/2014");
			size_t expected1 = 4;
			Assert::AreEqual(display1.size(), expected1);
			vector<vector<string>> display2 = test.displayTable("06/11/2014");
			size_t expected2 = 4;
			Assert::AreEqual(display2.size(), expected2);
		}
	};

}