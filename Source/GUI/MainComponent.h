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

enum TransportState
{
    Stopped, 
    Starting, 
    Playing, 
    Stopping
};

class MainComponent  : public juce::AudioAppComponent,
                       public juce::ChangeListener,
                       SampleLibraryDataModel::Listener
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

    //==============================================================================
    void changeListenerCallback(juce::ChangeBroadcaster*) override; 
    void changeState(TransportState); 
    void activeFileChanged(const SampleInfoDataModel&) override; 

private:
    //==============================================================================
    SampleLibraryDataModel m_sample_library;

    // GUI
    FileExplorer m_file_explorer;
    AddFilesButton m_add_files;
    VTWaveformDisplay m_waveform_display; 

    // Audio 
    juce::AudioFormatManager m_format_manager; 
    std::unique_ptr<juce::AudioFormatReaderSource> m_reader_source; 
    juce::AudioTransportSource m_transport_source; 
    TransportState m_transport_state; 
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
