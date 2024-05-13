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
    DECLARE_ID(name)
}

class SampleInfoDataModel
{
public: 
    explicit SampleInfoDataModel();
    SampleInfoDataModel(const juce::ValueTree&);
    SampleInfoDataModel(const SampleInfoDataModel&); 

    // Getters
    inline const juce::ValueTree State() const; 
    inline juce::String Name() const; 

    // Setters 
    void SetName(const juce::String); 

private: 

    juce::ValueTree vt; 
    juce::CachedValue<juce::String> name; 
 };