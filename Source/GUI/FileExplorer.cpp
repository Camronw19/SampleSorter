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
FileExplorer::FileExplorer(const SampleLibraryDataModel& sample_library)
    :m_file_list(sample_library)
{
      addAndMakeVisible(m_file_list); 

      addAndMakeVisible(m_search_bar); 
      m_search_bar.addListener(this); 
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
    
    m_search_bar.setBounds(bounds.removeFromTop(30)); 
    bounds.removeFromTop(spacing::padding1); 
    m_file_list.setBounds(bounds); 
}
