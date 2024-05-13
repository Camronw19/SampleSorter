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
    inline const juce::ValueTree State() const; 
    inline juce::String Name() const; 

    // Setters
    void SetName(const juce::String); 

private: 

    juce::ValueTree vt;
    juce::CachedValue<juce::String> name; 
};