/*
  ==============================================================================

    AddFilesComponent.h
    Created: 18 May 2024 6:14:30pm
    Author:  camro

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "FileUtils.h"
#include "SampleLibrary.h"

//==============================================================================
/*
*/
class AddFilesComponent  : public juce::Button, 
                           public AudioFileChooser
{
public:
    explicit AddFilesComponent(const SampleLibraryDataModel&);
    ~AddFilesComponent() override;

    void paintButton(juce::Graphics&, bool, bool) override;

private:
    void clicked() override; 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AddFilesComponent)
};
