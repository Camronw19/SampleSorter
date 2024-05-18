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
      m_name(m_vt, ModelIdentifiers::name, nullptr), 
      m_active_file(m_vt, ModelIdentifiers::active_file, nullptr)
{
    m_vt.addListener(this); 
}

SampleLibraryDataModel::SampleLibraryDataModel(const SampleLibraryDataModel& other)
    :SampleLibraryDataModel(other.getState())
{
}

SampleLibraryDataModel::SampleLibraryDataModel(const juce::ValueTree& vt)
    :m_vt(vt),
    m_name(m_vt, ModelIdentifiers::name, nullptr),
    m_active_file(m_vt, ModelIdentifiers::active_file, nullptr)
{
    m_vt.addListener(this); 
    jassert(vt.hasType(ModelIdentifiers::SAMPLE_LIBRARY)); 
}

SampleLibraryDataModel::~SampleLibraryDataModel()
{
    m_vt.removeListener(this); 
}

void SampleLibraryDataModel::valueTreeChildAdded(juce::ValueTree& parent, juce::ValueTree& added_child)
{
    if (added_child.hasType(ModelIdentifiers::SAMPLE_INFO))
    {
        m_listener_list.call([&](Listener& l) { l.sampleAdded(SampleInfoDataModel(added_child)); });
    }
}

void SampleLibraryDataModel::valueTreePropertyChanged(juce::ValueTree& tree_changed, const juce::Identifier& property)
{
    if (tree_changed.hasType(ModelIdentifiers::SAMPLE_LIBRARY))
    {
        if (property == ModelIdentifiers::active_file)
        {
            m_active_file.forceUpdateOfCachedValue(); 
            m_listener_list.call([&](Listener& l) { l.activeFileChanged(getActiveFile()); });
        }
    }
}

void SampleLibraryDataModel::addListener(Listener& listener)
{
    m_listener_list.add(&listener);
}

void SampleLibraryDataModel::removeListener(Listener& listener)
{
    m_listener_list.remove(&listener);
}

void SampleLibraryDataModel::AddSample(const SampleInfoDataModel& sample_info)
{
    m_vt.addChild(sample_info.getState(), -1, nullptr); 
}


SampleInfoDataModel SampleLibraryDataModel::getActiveFile() const
{
    juce::ValueTree sample_info(m_vt.getChildWithProperty(ModelIdentifiers::id, m_active_file.get())); 

    if (sample_info.hasType(ModelIdentifiers::SAMPLE_INFO))
        return sample_info; 
    else
        return SampleInfoDataModel(); 
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

void SampleLibraryDataModel::setActiveFile(const int file_id)
{
    m_active_file.setValue(file_id, nullptr); 
}


