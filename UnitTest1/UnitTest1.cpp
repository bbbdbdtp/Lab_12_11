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
			// ��������� ������ ��������� ������ ��� ����������
			HelpEntry* head = nullptr;
			addHelpEntry(head, "term1", "explanation1");
			addHelpEntry(head, "term2", "explanation2");
			addHelpEntry(head, "term3", "explanation3");

			// ���� 1: ����� ��������� ������
			std::string result1 = findExplanation(head, "term2");
			Assert::AreEqual(result1, std::string("explanation2"));

			// ���� 2: ����� ���������� ������
			std::string result2 = findExplanation(head, "term4");
			Assert::AreEqual(result2, std::string("Explanation not found."));

			// ��������� ���'�� ���� �����
			deleteHelpList(head);
		}
	};
}
