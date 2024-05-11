#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			const std::string name = "test"; 
			const std::string name2 = "test"; 
			Assert::AreEqual(name, name2);
		}
	};
}
