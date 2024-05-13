#include "pch.h"
#include "CppUnitTest.h"
#include "SampleLibrary.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTest1
{
	TEST_CLASS(SampleLibraryTests)
	{
	public:

		TEST_METHOD(Constructor_DefualtConstructsValidObject)
		{
			SampleLibraryDataModel sample_library; 
			Assert::IsTrue(sample_library.State().hasType(ModelIdentifiers::SAMPLE_LIBRARY));
		}

		TEST_METHOD(Constructor_CopyContructsValidObject)
		{
			SampleLibraryDataModel original;
			original.SetName(juce::String("TEST"));

			SampleLibraryDataModel copy(original);

			Assert::AreEqual(original.Name().toStdString(), copy.Name().toStdString());
		}
	};
}
