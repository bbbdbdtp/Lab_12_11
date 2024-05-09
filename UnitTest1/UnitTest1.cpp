#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_12_11/Main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestfindExplanation)
		{
			// Створення списку допоміжних записів для тестування
			HelpEntry* head = nullptr;
			addHelpEntry(head, "term1", "explanation1");
			addHelpEntry(head, "term2", "explanation2");
			addHelpEntry(head, "term3", "explanation3");

			// Тест 1: Пошук існуючого терміну
			std::string result1 = findExplanation(head, "term2");
			Assert::AreEqual(result1, std::string("explanation2"));

			// Тест 2: Пошук неіснуючого терміну
			std::string result2 = findExplanation(head, "term4");
			Assert::AreEqual(result2, std::string("Explanation not found."));

			// Звільнення пам'яті після тесту
			deleteHelpList(head);
		}
	};
}
