/*
  ==============================================================================

    SampleLibrary.cpp
    Created: 13 May 2024 11:21:38am
    Author:  camro

  ==============================================================================
*/

#include "SampleLibrary.h"

SampleLibraryDataModel::SampleLibraryDataModel()
    : SampleLibraryDataModel(juce::ValueTree(ModelIdentifiers::SAMPLE_LIBRARY))
{

}

SampleLibraryDataModel::SampleLibraryDataModel(const SampleLibraryDataModel& other)
    :SampleLibraryDataModel(other.getState())
{

}

SampleLibraryDataModel::SampleLibraryDataModel(const juce::ValueTree& value_tree)
    :vt(value_tree),
    name(vt, ModelIdentifiers::name, nullptr)
{
    jassert(vt.hasType(ModelIdentifiers::SAMPLE_LIBRARY)); 
}

void SampleLibraryDataModel::AddSample(const SampleInfoDataModel& sample_info)
{
    vt.addChild(sample_info.getState(), -1, nullptr); 
}

// Getters

inline const juce::ValueTree SampleLibraryDataModel::getState() const
{
    return vt; 
}


inline juce::String SampleLibraryDataModel::getName() const
{
    return name.get(); 
}

// Setters 

void SampleLibraryDataModel::setName(const juce::String new_name)
{
    name.setValue(new_name, nullptr);
}