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
    DECLARE_ID(active_file)
}

class SampleLibraryDataModel : private juce::ValueTree::Listener
{
public: 
    class Listener
    {
    public:
        virtual ~Listener() noexcept = default;
        virtual void sampleAdded(const SampleInfoDataModel&) {};
        virtual void activeFileChanged(const SampleInfoDataModel&) {}; 
    };

    explicit SampleLibraryDataModel(); 
    ~SampleLibraryDataModel(); 
    SampleLibraryDataModel(const SampleLibraryDataModel&);

    void AddSample(const SampleInfoDataModel&);

    // Getters
    const juce::ValueTree getState() const; 
    juce::String getName() const; 
    SampleInfoDataModel getActiveFile() const; 

    // Setters
    void setName(const juce::String); 
    void setActiveFile(const int); 

    void addListener(Listener&);
    void removeListener(Listener&);

private: 
    SampleLibraryDataModel(const juce::ValueTree&); 
    virtual void valueTreeChildAdded(juce::ValueTree&, juce::ValueTree&) override; 
    virtual void valueTreePropertyChanged(juce::ValueTree&, const juce::Identifier&) override; 

    juce::ValueTree m_vt;
    juce::CachedValue<int> m_active_file; 
    juce::CachedValue<juce::String> m_name; 

    juce::ListenerList<Listener> m_listener_list; 
};