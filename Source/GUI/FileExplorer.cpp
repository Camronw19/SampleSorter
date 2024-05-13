/*
  ==============================================================================

    FileExplorer.cpp
    Created: 13 May 2024 6:20:10pm
    Author:  camro

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FileExplorer.h"

//==============================================================================
FileExplorer::FileExplorer()
    :m_file_list(m_sample_library.getState())
{
    for (int i = 0; i < 3; i++)
    {
        SampleInfoDataModel sample_model; 
        sample_model.setName("TEST " + juce::String(i)); 
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
    auto bounds = getBounds(); 
    m_file_list.setBounds(bounds); 
}
