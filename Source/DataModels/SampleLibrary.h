/*
  ==============================================================================

    SampleLibrary.h
    Created: 13 May 2024 11:21:38am
    Author:  camro

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SampleInfo.h"

namespace ModelIdentifiers
{
    DECLARE_ID(SAMPLE_LIBRARY)
}

class SampleLibraryDataModel
{
public: 
    explicit SampleLibraryDataModel(); 
    SampleLibraryDataModel(const juce::ValueTree&); 
    SampleLibraryDataModel(const SampleLibraryDataModel&);

    void AddSample(const SampleInfoDataModel&); 

    // Getters
    const juce::ValueTree getState() const; 
    juce::String getName() const; 

    // Setters
    void setName(const juce::String); 

private: 

    juce::ValueTree m_vt;
    juce::CachedValue<juce::String> m_name; 
};