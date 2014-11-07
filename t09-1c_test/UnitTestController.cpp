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
		
		
		TEST_METHOD(Event1)
		{
			vector<string> testVector;
			string testString, testString2;
			testVector.push_back("<CreationDate>07/10/2014 22:26</CreationDate><name>meet prof</name><date>10/10/2014</date><start>10:00</start><end>12:00</end><category></category><type>timed</type><complete>yes</complete>");
			ProgramController test(testVector);
			//testVector = test.returnTestVector();
			test.executeEntry("add [test1][051114][1300][testing]");
			testString = "<name>test1</name><date>05/11/2014</date><start></start><end>13:00</end><category>testing</category><complete>no</complete><type>deadline</type>";
			testString2 = test.returnTestVector()[1];
			Assert::AreEqual(testString, testString2);
		}
		TEST_METHOD(Event2)
		{
			vector<string> testVector;
			string testString, testString2;
			testVector.push_back("<name>meet prof</name><date>10/12/2014</date><start>10:00</start><end>12:00</end><category></category><complete>yes</complete><type>timed</type>");
			ProgramController test(testVector);
			//testVector = test.returnTestVector();
			test.executeEntry("edit 1 [test1][051114][1300][testing]");
			testString = "<name>test1</name><date>05/11/2014</date><start></start><end>13:00</end><category>testing</category><complete>no</complete><type>deadline</type>";
			testString2 = test.returnTestVector()[0];
			Assert::AreEqual(testString, testString2);
		}
		TEST_METHOD(Event3)
		{
			vector<string> testVector;
			string testString, testString2;
			testVector.push_back("<CreationDate>07/11/2014 22:26</CreationDate><name>meet prof</name><date>10/12/2014</date><start>10:00</start><end>12:00</end><category></category><complete>yes</complete><type>timed</type>");
			ProgramController test(testVector);
			//testVector = test.returnTestVector();
			test.executeEntry("add [test1][051114][1300][testing]");
			test.executeEntry("edit 2 [test1][051114][1300][testing]");
			testString = "<name>test1</name><date>05/11/2014</date><start></start><end>13:00</end><category>testing</category><complete>no</complete><type>deadline</type>";
			testString2 = test.returnTestVector()[1];
			Assert::AreEqual(testString, testString2);
		}
		/*<CreationDate>07 / 10 / 2014 22:26< / CreationDate><name>meet prof< / name><date>10 / 10 / 2014< / date><start>10 : 00< / start><end>12 : 00< / end><category>< / category><type>timed< / type><complete>yes< / complete>
			<CreationDate>09 / 10 / 2014 07 : 50< / CreationDate><name>midterm< / name><date>13 / 10 / 2014< / date><start>09 : 00< / start><end>11 : 00< / end><category>ee2021< / category><type>timed< / type><complete>yes< / complete>
			<CreationDate>09 / 10 / 2014 09 : 12< / CreationDate><name>hbfhfdbf< / name><date>12 / 10 / 2014< / date><start>< / start><end>12 : 00< / end><category>< / category><type>deadline< / type><complete>no< / complete>
			<CreationDate>13 / 10 / 2014 18 : 41< / CreationDate><name>meet prof< / name><date>20 / 10 / 2014< / date><start>< / start><end>23 : 59< / end><category>< / category><type>deadline< / type><complete>no< / complete>
			<CreationDate>13 / 10 / 2014 18 : 42< / CreationDate><name>do d2a lab< / name><date>20 / 10 / 2014< / date><start>02 : 00< / start><end>05 : 00< / end><category>< / category><type>timed< / type><complete>no< / complete>
			<CreationDate>22 / 10 / 2014 21 : 35< / CreationDate><name>eat blueberry< / name><date>27 / 10 / 2014< / date><start>06 : 00< / start><end>08 : 00< / end><category>< / category><type>timed< / type><complete>yes< / complete>
			<CreationDate>27 / 10 / 2014 21 : 40< / CreationDate><name>hello< / name><date>01 / 11 / 2014< / date><start>21 : 00< / start><end>04 : 00 + 1< / end><category>< / category><type>timed< / type><complete>no< / complete>
			<CreationDate>28 / 10 / 2014 10 : 27< / CreationDate><name>meet somebody< / name><date>03 / 11 / 2014< / date><start>08 : 00< / start><end>10 : 00< / end><category>< / category><type>timed< / type><complete>no< / complete>
			<CreationDate>29 / 10 / 2014 18 : 37< / CreationDate><name>VHDL test< / name><date>03 / 11 / 2014< / date><start>14 : 00< / start><end>17 : 00< / end><category>exam< / category><type>timed< / type><complete>no< / complete>
			*/
	};
}