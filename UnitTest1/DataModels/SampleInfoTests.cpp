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
			Assert::IsTrue(sample_info.getState().hasType(ModelIdentifiers::SAMPLE_INFO));
		}

		TEST_METHOD(Constructor_CopyContructsValidObject)
		{
			SampleInfoDataModel original; 
			original.setName(juce::String("TEST"));

			SampleInfoDataModel copy(original);

			Assert::AreEqual(original.getName().toStdString(), copy.getName().toStdString());
			Assert::IsTrue(original.getState() == copy.getState());
		}

		TEST_METHOD(Setter_SetState)
		{
			juce::ValueTree value_tree(ModelIdentifiers::SAMPLE_INFO); 
			SampleInfoDataModel sample_info(value_tree); 

			Assert::IsTrue(value_tree == sample_info.getState()); 
		}

		TEST_METHOD(Setter_SetName)
		{
			SampleInfoDataModel sample_info; 
			juce::String name = "TEST"; 
			sample_info.setName(name);

			Assert::AreEqual(name.toStdString(), sample_info.getName().toStdString());
		}

		TEST_METHOD(Setter_SetName_EmptyString)
		{
			SampleInfoDataModel sample_info;
			juce::String name = "";
			sample_info.setName(name);

			Assert::AreEqual(name.toStdString(), sample_info.getName().toStdString());
		}

		TEST_METHOD(Setter_SetName_SpecialCharacters)
		{
			SampleInfoDataModel sample_info;
			juce::String name = "Tëst!@#$%^&*()";
			sample_info.setName(name);

			Assert::AreEqual(name.toStdString(), sample_info.getName().toStdString());
		}
	};
}
