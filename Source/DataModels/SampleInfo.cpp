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
    : SampleInfoDataModel(juce::ValueTree(ModelIdentifiers::SAMPLE_INFO))
{
    m_id.setValue(m_instance_id, nullptr);
    ++m_instance_id;
}


SampleInfoDataModel::SampleInfoDataModel(const juce::ValueTree& vt)
    : m_vt(vt),
    m_id(m_vt, ModelIdentifiers::id, nullptr),
    m_name(m_vt, ModelIdentifiers::name, nullptr),
    m_file_path(m_vt, ModelIdentifiers::file_path, nullptr), 
    m_is_favorite(m_vt, ModelIdentifiers::is_favorite, nullptr),
    m_file_extension(m_vt, ModelIdentifiers::file_extension, nullptr)
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

juce::String SampleInfoDataModel::getFilePath() const
{
    return m_file_path; 
}

juce::String SampleInfoDataModel::getFileExtension() const
{
    return m_file_extension; 
}

bool SampleInfoDataModel::isFavorite() const
{
    return m_is_favorite; 
}

// Setters 
void SampleInfoDataModel::setName(const juce::String name)
{
    m_name.setValue(name, nullptr); 
}

void SampleInfoDataModel::setFilePath(const juce::String file_path)
{
    m_file_path.setValue(file_path, nullptr); 
}

void SampleInfoDataModel::setFileExtension(const juce::String file_extension)
{
    m_file_extension.setValue(file_extension, nullptr); 
}

void SampleInfoDataModel::setIsFavorite(const bool is_favorite)
{
    m_is_favorite.setValue(is_favorite, nullptr); 
}