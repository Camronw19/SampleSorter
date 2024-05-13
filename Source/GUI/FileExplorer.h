/*
  ==============================================================================

    FileExplorer.h
    Created: 13 May 2024 6:20:10pm
    Author:  camro

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SampleLibrary.h"
#include "FileDisplayComponents.h"

//==============================================================================
/*
*/
class FileExplorer  : public juce::Component
{
public:
    FileExplorer();
    ~FileExplorer() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    SampleLibraryDataModel m_sample_library;
    FileList m_file_list;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FileExplorer)
};
