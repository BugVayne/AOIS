#include "pch.h"
#include "CppUnitTest.h"
#include "SpreadsheetOfTruth.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTest1
{
	TEST_CLASS(SpreadsheetOfTruthTest)
	{
	public:

		TEST_METHOD(InitTest)
		{

			string formula = "( ( !  ( ( A & B ) > D )  ) | ( A | ( B ~ D ) ) )";
			SpreadsheetOfTruth sheetk(formula);
		}
		TEST_METHOD(PrintFormulesTest)
		{
			string formula = "( ( !  ( ( A & B ) > D )  ) | ( A | ( B ~ D ) ) )";
			SpreadsheetOfTruth sheetk(formula);

			stringstream buf;
			streambuf* oldbuf = cout.rdbuf(buf.rdbuf());
			sheetk.PrintFormules();
			cout.rdbuf(oldbuf);
			string output = buf.str();
			char ch = output[0];
			Assert::AreEqual(ch, ' ');

		}
		TEST_METHOD(PrintTableTest)
		{
			string formula = "( ( !  ( ( A & B ) > D )  ) | ( A | ( B ~ D ) ) )";
			SpreadsheetOfTruth sheetk(formula);

			stringstream buf;
			streambuf* oldbuf = cout.rdbuf(buf.rdbuf());
			sheetk.Printsheet();
			cout.rdbuf(oldbuf);
			string output = buf.str();
			char ch = output[0];
			Assert::AreEqual(ch, ' ');

		}
	};
}
