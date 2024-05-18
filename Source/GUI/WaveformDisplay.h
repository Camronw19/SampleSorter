/*
  ==============================================================================

    WaveformDisplay.h
    Created: 18 May 2024 8:50:25am
    Author:  camro

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SampleLibrary.h"

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component, 
                         public juce::ChangeListener
{
public:
    WaveformDisplay();
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setThumbnailSource(const juce::File&); 

private:
    void changeListenerCallback(juce::ChangeBroadcaster*) override; 
    void thumbnailChanged(); 

    void paintIfNoFileLoaded(juce::Graphics&, juce::Rectangle<int>&); 
    void paintIfFileLoaded(juce::Graphics&, juce::Rectangle<int>&); 

    juce::AudioFormatManager m_format_manager; 
    juce::AudioThumbnailCache m_thumbnail_cache; 
    juce::AudioThumbnail m_thumbnail; 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};

class VTWaveformDisplay : public WaveformDisplay,
                          public SampleLibraryDataModel::Listener
{
public: 
    explicit VTWaveformDisplay(const SampleLibraryDataModel&); 
    ~VTWaveformDisplay(); 

private:

    void activeFileChanged(const SampleInfoDataModel&) override; 

    SampleLibraryDataModel m_sample_library; 


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VTWaveformDisplay)
};
