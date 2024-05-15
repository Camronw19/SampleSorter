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

class SampleLibraryDataModel : public juce::ValueTree::Listener
{
public: 
    class Listener
    {
    public:
        virtual ~Listener() noexcept = default;
        virtual void SampleAdded(const SampleInfoDataModel&) {};
    };

    explicit SampleLibraryDataModel(); 
    ~SampleLibraryDataModel(); 
    SampleLibraryDataModel(const juce::ValueTree&); 
    SampleLibraryDataModel(const SampleLibraryDataModel&);

    void AddSample(const SampleInfoDataModel&); 

    // Getters
    const juce::ValueTree getState() const; 
    juce::String getName() const; 

    // Setters
    void setName(const juce::String); 

    void addListener(Listener&);
    void removeListener(Listener&);
private: 
    virtual void valueTreeChildAdded(juce::ValueTree&, juce::ValueTree&) override; 

    juce::ValueTree m_vt;
    juce::CachedValue<juce::String> m_name; 

    juce::ListenerList<Listener> m_listener_list; 
};