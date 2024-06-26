#pragma once

#include <JuceHeader.h>
#include "FileExplorer.h"
#include "WaveformDisplay.h"
#include "AddFiles.h"
#include "UIConfig.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    SampleLibraryDataModel m_sample_library;

    FileExplorer m_file_explorer;
    AddFilesButton m_add_files;
    VTWaveformDisplay m_waveform_display; 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
