#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
    :m_file_explorer(m_sample_library), 
     m_waveform_display(m_sample_library), 
     m_add_files(m_sample_library), 
     m_transport_state(Stopped)
{ 
    addAndMakeVisible(m_file_explorer);
    addAndMakeVisible(m_add_files);
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

    m_format_manager.registerBasicFormats(); 
    m_transport_source.addChangeListener(this);
    m_sample_library.addListener(*this); 
}

MainComponent::~MainComponent()
{

    setLookAndFeel(nullptr); 
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    m_transport_source.prepareToPlay(samplesPerBlockExpected, sampleRate); 
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (m_reader_source.get() == nullptr)
    {
        bufferToFill.clearActiveBufferRegion(); 
        return;
    }

    m_transport_source.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    m_transport_source.releaseResources(); 
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (AppColors::ColourIds::Background));
}

void MainComponent::resized()
{
    auto bounds = getLocalBounds().reduced(spacing::padding2); 

    m_add_files.setBounds(bounds.removeFromTop(40).removeFromLeft(getWidth() / 6));
    bounds.removeFromTop(spacing::padding2);

    m_file_explorer.setBounds(bounds.removeFromTop(getHeight() / 1.5)); 
    bounds.removeFromTop(spacing::padding2);

    m_waveform_display.setBounds(bounds); 
}


void MainComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &m_transport_source)
    {
        if (m_transport_source.isPlaying())
            changeState(Playing);
        else
            changeState(Stopped);
    }
}


void MainComponent::changeState(TransportState new_state)
{
    if (m_transport_state != new_state)
    {
        m_transport_state = new_state;

        switch (m_transport_state)
        {
        case Stopped:
            //stopButton.setEnabled(false);
            //playButton.setEnabled(true);
           m_transport_source.setPosition(0.0);
            break;

        case Starting:
            //playButton.setEnabled(false);
            m_transport_source.start();
            break;

        case Playing:
            //stopButton.setEnabled(true);
            break;

        case Stopping:
            m_transport_source.stop();
            break;
        }
    }
}


void MainComponent::activeFileChanged(const SampleInfoDataModel& active_sample)
{
    juce::File sample_file(active_sample.getFilePath()); 
    auto* reader = m_format_manager.createReaderFor(sample_file);

    if (reader != nullptr)
    {
        auto newSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
        m_transport_source.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        //playButton.setEnabled(true);
        m_reader_source.reset(newSource.release());
        changeState(Starting); 
    }
}
