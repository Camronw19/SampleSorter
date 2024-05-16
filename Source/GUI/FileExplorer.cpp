/*
  ==============================================================================

    FileExplorer.cpp
    Created: 13 May 2024 6:20:10pm
    Author:  camro

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FileExplorer.h"
#include "UIConfig.h"

//==============================================================================
FileExplorer::FileExplorer()
    :m_file_list(m_sample_library)
{
    for (int i = 0; i < 5; i++)
    {
        SampleInfoDataModel sample_model;

        juce::String id(sample_model.getId());
        sample_model.setName("Sample Info " + id); 
        sample_model.setFileExtension(".wav"); 
        m_sample_library.AddSample(sample_model); 
    }

    addAndMakeVisible(m_file_list); 
}

FileExplorer::~FileExplorer()
{
}

void FileExplorer::paint (juce::Graphics& g)
{

}

void FileExplorer::resized()
{
    auto bounds = getLocalBounds(); 
    m_file_list.setBounds(bounds.reduced(spacing::padding2)); 
}
