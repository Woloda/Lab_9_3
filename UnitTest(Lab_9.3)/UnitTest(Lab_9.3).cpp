#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_9.3/Lab_9.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLab93
{
	TEST_CLASS(UnitTestLab93)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			int zmina = 0;
			int kil_towar = 2;
			int soxr_towar = kil_towar;
			towar* s = new towar[kil_towar + 1000];

			s[0].n_towar = "вовка";            s[1].n_towar = "азбука";
			s[0].vartіst = 120;                s[1].vartіst = 10;
			s[0].kilkist = 12;                 s[1].kilkist = 13;
			s[0].units = (measurement)0; 	   s[1].units = (measurement)1;
			s[0].masa = 20;                    s[1].masa = 10;

			Sort(s, kil_towar, zmina);

			Assert::AreEqual(s[0].vartіst, 10);
		}
	};
}
