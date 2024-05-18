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
			Assert::IsTrue(sample_library.getState().hasType(ModelIdentifiers::SAMPLE_LIBRARY));
		}

		TEST_METHOD(Constructor_CopyContructsValidObject)
		{
			SampleLibraryDataModel original;
			original.setName(juce::String("TEST"));

			SampleLibraryDataModel copy(original);

			Assert::AreEqual(original.getName().toStdString(), copy.getName().toStdString());
		}

		TEST_METHOD(Setter_SetState)
		{
			juce::ValueTree value_tree(ModelIdentifiers::SAMPLE_LIBRARY);
			SampleLibraryDataModel sample_library(value_tree);

			Assert::IsTrue(value_tree == sample_library.getState());
		}

		TEST_METHOD(Setter_SetName)
		{
			SampleLibraryDataModel sample_library;
			juce::String name = "TEST";
			sample_library.setName(name);

			Assert::AreEqual(name.toStdString(), sample_library.getName().toStdString());
		}

		TEST_METHOD(Setter_SetName_EmptyString)
		{
			SampleLibraryDataModel sample_library;
			juce::String name = "";
			sample_library.setName(name);

			Assert::AreEqual(name.toStdString(), sample_library.getName().toStdString());
		}

		TEST_METHOD(Setter_SetName_SpecialCharacters)
		{
			SampleLibraryDataModel sample_library;
			juce::String name = "Tëst!@#$%^&*()";
			sample_library.setName(name);

			Assert::AreEqual(name.toStdString(), sample_library.getName().toStdString());
		}

		TEST_METHOD(AddSample)
		{
			SampleLibraryDataModel sample_library; 

			for (int i = 1; i < 5; i++)
			{
				SampleInfoDataModel sample_model;

				juce::String id(sample_model.getId());
				sample_model.setName("Sample Info " + id);
				sample_library.AddSample(sample_model);

				Assert::IsTrue(sample_library.getState().getNumChildren() == i); 
			}
		}
	};
}
