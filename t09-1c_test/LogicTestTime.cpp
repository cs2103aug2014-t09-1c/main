//@author A0116410Y
#include "stdafx.h"
#include "CppUnitTest.h"
#include "TimeLogic.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace t091c_test
{
	TEST_CLASS(LogicTestTime)
	{
	public:
		
		TEST_METHOD(TIME_COMPARE_CHECK)
		{
			TimeLogic time1test1("01/11/2014", "00:00");
			TimeLogic time2test1("01/11/2014", "00:00+1");
			Assert::IsTrue(TimeLogic::isFirstEarlierThanSecond(time1test1, time2test1));
			TimeLogic time1test2("02/11/2014", "00:00");
			TimeLogic time2test2("01/11/2014", "00:00+1");
			Assert::IsTrue(TimeLogic::isFirstEarlierThanSecond(time1test2, time2test2));
			TimeLogic time1test3("23/11/2014", "00:00");
			TimeLogic time2test3("21/11/2014", "00:00+1");
			Assert::IsFalse(TimeLogic::isFirstEarlierThanSecond(time1test3, time2test3));
		}
		TEST_METHOD(ADD_HOURS_CHECK)
		{
			TimeLogic time1test1("01/11/2014", "00:00");
			time1test1.addHours(3, 33);
			Assert::IsTrue(time1test1.getStringDate() == "01/11/2014");
			Assert::IsTrue(time1test1.getStringTime() == "03:33");
			TimeLogic time1test2("01/11/2014", "00:01");
			time1test2.addHours(23, 59);
			Assert::IsTrue(time1test2.getStringDate() == "02/11/2014");
			Assert::IsTrue(time1test2.getStringTime() == "00:00");
			TimeLogic time1test3("01/11/2014", "00:01+1");
			time1test3.addHours(1, 0);
			Assert::IsTrue(time1test3.getStringDate() == "02/11/2014");
			Assert::IsTrue(time1test3.getStringTime() == "01:01");
			TimeLogic time1test4("01/11/2014", "00:01+1");
			time1test4.addHours(23, 59);
			Assert::IsTrue(time1test4.getStringDate() == "02/11/2014");
			Assert::IsTrue(time1test4.getStringTime() == "00:01");
		}

	};
}