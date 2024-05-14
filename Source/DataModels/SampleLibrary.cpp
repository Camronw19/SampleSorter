/*
  ==============================================================================

    SampleLibrary.cpp
    Created: 13 May 2024 11:21:38am
    Author:  camro

  ==============================================================================
*/

#include "SampleLibrary.h"

SampleLibraryDataModel::SampleLibraryDataModel()
    : m_vt(juce::ValueTree(ModelIdentifiers::SAMPLE_LIBRARY)),
      m_name(m_vt, ModelIdentifiers::name, nullptr)
{

}

SampleLibraryDataModel::SampleLibraryDataModel(const SampleLibraryDataModel& other)
    :SampleLibraryDataModel(other.getState())
{

}

SampleLibraryDataModel::SampleLibraryDataModel(const juce::ValueTree& vt)
    :m_vt(vt),
    m_name(m_vt, ModelIdentifiers::name, nullptr)
{
    jassert(vt.hasType(ModelIdentifiers::SAMPLE_LIBRARY)); 
}

void SampleLibraryDataModel::AddSample(const SampleInfoDataModel& sample_info)
{
    m_vt.addChild(sample_info.getState(), -1, nullptr); 
}

// Getters

const juce::ValueTree SampleLibraryDataModel::getState() const
{
    return m_vt; 
}


juce::String SampleLibraryDataModel::getName() const
{
    return m_name.get(); 
}

// Setters 

void SampleLibraryDataModel::setName(const juce::String new_name)
{
    m_name.setValue(new_name, nullptr);
}