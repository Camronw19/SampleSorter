#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
    :m_file_explorer(m_sample_library), 
     m_waveform_display(m_sample_library)
{ 
    addAndMakeVisible(m_file_explorer);
    addAndMakeVisible(m_waveform_display); 

    setSize (800, 600);

    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        setAudioChannels (2, 2);
    }

    for (int i = 0; i < 5; i++)
    {
        SampleInfoDataModel sample_model;

        juce::String id(sample_model.getId());
        sample_model.setName("Sample Info " + id); 
        sample_model.setFileExtension(".wav"); 
        DBG("ADDING FILE"); 
        m_sample_library.AddSample(sample_model); 
    }
}

MainComponent::~MainComponent()
{

    setLookAndFeel(nullptr); 
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{

}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{

    bufferToFill.clearActiveBufferRegion();
}

void MainComponent::releaseResources()
{

}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (AppColors::ColourIds::Background));
}

void MainComponent::resized()
{
    auto bounds = getLocalBounds(); 
    m_file_explorer.setBounds(bounds.removeFromTop(getHeight() / 1.5)); 

    bounds.removeFromTop(spacing::padding4);

    m_waveform_display.setBounds(bounds); 
}
