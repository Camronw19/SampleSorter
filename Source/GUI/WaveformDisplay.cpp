/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 18 May 2024 8:50:25am
    Author:  camro

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"
#include "UIConfig.h"

//==============================================================================
WaveformDisplay::WaveformDisplay()
    : m_thumbnail_cache(5), 
      m_thumbnail(1024, m_format_manager, m_thumbnail_cache)
{
    m_format_manager.registerBasicFormats(); 
    m_thumbnail.addChangeListener(this); 
}

WaveformDisplay::~WaveformDisplay()
{
    m_thumbnail.removeChangeListener(this); 
}

void WaveformDisplay::paint (juce::Graphics& g)
{

    juce::Rectangle<int> bounds = getLocalBounds(); 
    juce::Rectangle<int> thumbnail_bounds = bounds.reduced(0, spacing::padding1); 

    g.setColour(getLookAndFeel().findColour(AppColors::Surface1dp));
    g.fillRoundedRectangle(bounds.toFloat(), rounding::rounding1);

    if (m_thumbnail.getNumChannels() == 0)
        paintIfNoFileLoaded(g, thumbnail_bounds);
    else
        paintIfFileLoaded(g, thumbnail_bounds); 
}

void WaveformDisplay::resized()
{

}

void WaveformDisplay::setThumbnailSource(const juce::File& inputSource)
{
    m_thumbnail.setSource(new juce::FileInputSource(inputSource)); 
}

void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &m_thumbnail)
        thumbnailChanged();
}

void WaveformDisplay::thumbnailChanged()
{
    repaint(); 
}

void WaveformDisplay::paintIfNoFileLoaded(juce::Graphics& g, juce::Rectangle<int>& thumbnail_bounds)
{
    g.setColour(getLookAndFeel().findColour(AppColors::ColourIds::Primary));
    g.drawFittedText("No File Loaded", thumbnail_bounds, juce::Justification::centred, 1);
}

void WaveformDisplay::paintIfFileLoaded(juce::Graphics& g, juce::Rectangle<int>& thumbnail_bounds)
{
    g.setColour(getLookAndFeel().findColour(AppColors::ColourIds::Primary));
    m_thumbnail.drawChannels(g, thumbnail_bounds, 0.0, m_thumbnail.getTotalLength(), 1.0f);
}

//==============================================================================

VTWaveformDisplay::VTWaveformDisplay(const SampleLibraryDataModel& sample_library)
    :m_sample_library(sample_library)
{
    m_sample_library.addListener(*this); 
}

VTWaveformDisplay::~VTWaveformDisplay()
{
    m_sample_library.removeListener(*this); 
}

void VTWaveformDisplay::activeFileChanged(const SampleInfoDataModel& sample_info)
{
        juce::File file(sample_info.getFilePath()); 

        if (file.exists())
            setThumbnailSource(file);
        else
            setThumbnailSource(juce::File()); 
}
