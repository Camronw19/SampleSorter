/*
  ==============================================================================

    SampleInfo.cpp
    Created: 13 May 2024 10:47:39am
    Author:  camro

  ==============================================================================
*/

#include "SampleInfo.h"

int32_t SampleInfoDataModel::m_instance_id = 1; 

SampleInfoDataModel::SampleInfoDataModel()
    : m_vt(juce::ValueTree(ModelIdentifiers::SAMPLE_INFO)),
    m_id(m_vt, ModelIdentifiers::id, nullptr),
    m_name(m_vt, ModelIdentifiers::name, nullptr)
{
    m_id.setValue(m_instance_id, nullptr);
    ++m_instance_id;
}


SampleInfoDataModel::SampleInfoDataModel(const juce::ValueTree& vt)
    : m_vt(vt),
    m_id(m_vt, ModelIdentifiers::id, nullptr),
    m_name(m_vt, ModelIdentifiers::name, nullptr)
{
    jassert(vt.hasType(ModelIdentifiers::SAMPLE_INFO));
}

SampleInfoDataModel::SampleInfoDataModel(const SampleInfoDataModel& other)
    : SampleInfoDataModel(other.getState())
{

}

// Getters
const juce::ValueTree SampleInfoDataModel::getState() const
{
    return m_vt; 
}

int32_t SampleInfoDataModel::getId() const
{
    return m_id; 
}

juce::String SampleInfoDataModel::getName() const
{
    return m_name.get(); 
}

// Setters 

void SampleInfoDataModel::setName(const juce::String new_name)
{
    m_name.setValue(new_name, nullptr); 
}