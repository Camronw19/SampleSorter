/*
  ==============================================================================

    SampleInfo.h
    Created: 13 May 2024 10:47:39am
    Author:  camro

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace ModelIdentifiers
{
    #define DECLARE_ID(name) const juce::Identifier(name) (#name); 

    DECLARE_ID(SAMPLE_INFO)
    DECLARE_ID(id)
    DECLARE_ID(name)
}

class SampleInfoDataModel
{
public: 
    explicit SampleInfoDataModel();
    SampleInfoDataModel(const juce::ValueTree&);
    SampleInfoDataModel(const SampleInfoDataModel&); 

    // Getters
    const juce::ValueTree getState() const; 
    int32_t getId() const; 
    juce::String getName() const; 

    // Setters 
    void setName(const juce::String); 

private: 
    static int32_t m_instance_id; 

    juce::ValueTree m_vt; 
    juce::CachedValue<int32_t> m_id; 
    juce::CachedValue<juce::String> m_name; 
 };