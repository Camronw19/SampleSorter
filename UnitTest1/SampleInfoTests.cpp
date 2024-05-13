#include "pch.h"
#include "CppUnitTest.h"
#include "SampleInfo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTest1
{
	TEST_CLASS(SampleInfoTests)
	{
	public:

		TEST_METHOD(Constructor_DefualtConstructsValidObject)
		{
			SampleInfoDataModel sample_info; 
			Assert::IsTrue(sample_info.State().getType() == ModelIdentifiers::SAMPLE_INFO);
		}

		TEST_METHOD(Constructor_CopyContructsValidObject)
		{
			SampleInfoDataModel original; 
			original.SetName(juce::String("TEST"));

			SampleInfoDataModel copy(original);

			Assert::AreEqual(original.Name().toStdString(), copy.Name().toStdString());
		}
	};
}
