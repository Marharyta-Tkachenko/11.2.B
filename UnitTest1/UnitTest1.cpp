#include "pch.h"
#include "CppUnitTest.h"
#include "../Project11.2.B/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			student s;

			fstream file_s("C:\\Моя папка\\Student [Tkachenko.Marharyta.IK-11]\\Lab_11.2.B\Lab_11.2.B\\test", ios::binary);

			s.prizv = "pip";
			s.kurs = 3;
			s.specialization = (Special)4;
			s.phisuka = 5;
			s.matematic = 5;
			s.chuslo_metod = 4;

			file_s.write((char*)&s, sizeof(student));
			file_s.close();

			file_s.open("C:\\Моя папка\\Student [Tkachenko.Marharyta.IK-11]\\Lab_11.2.B\Lab_11.2.B\\test", ios::binary);

			s.prizv = "pop";
			s.kurs = 2;
			s.specialization = (Special)3;
			s.phisuka = 4;
			s.matematic = 4;
			s.chuslo_metod = 4;

			file_s.write((char*)&s, sizeof(student));
			file_s.close();

			ifstream file_ll("C:\\Моя папка\\Student [Tkachenko.Marharyta.IK-11]\\Lab_11.2.B\Lab_11.2.B\\test", ios::binary);
			double l = find_prozent(s, 3, file_ll);
			file_ll.close();

			Assert::AreEqual(l, 100.0);
		}
	};
}
