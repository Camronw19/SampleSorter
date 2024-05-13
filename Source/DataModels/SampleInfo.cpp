/*
  ==============================================================================

    SampleInfo.cpp
    Created: 13 May 2024 10:47:39am
    Author:  camro

  ==============================================================================
*/

#include "SampleInfo.h"


SampleInfoDataModel::SampleInfoDataModel()
    : SampleInfoDataModel(juce::ValueTree(ModelIdentifiers::SAMPLE_INFO))
{

}


SampleInfoDataModel::SampleInfoDataModel(const juce::ValueTree& value_tree)
    : vt(value_tree),
    name(vt, ModelIdentifiers::name, nullptr)
{
    jassert(value_tree.hasType(ModelIdentifiers::SAMPLE_INFO));
}

SampleInfoDataModel::SampleInfoDataModel(const SampleInfoDataModel& other)
    :SampleInfoDataModel(other.getState())
{
 
}

// Getters
const juce::ValueTree SampleInfoDataModel::getState() const
{
    return vt; 
}


juce::String SampleInfoDataModel::getName() const
{
    return name.get(); 
}

// Setters 

void SampleInfoDataModel::setName(const juce::String new_name)
{
    name.setValue(new_name, nullptr); 
}