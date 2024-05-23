/*
  ==============================================================================

    AddFilesComponent.cpp
    Created: 18 May 2024 6:14:30pm
    Author:  camro

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AddFiles.h"
#include "UIConfig.h"

//==============================================================================
AddFilesButton::AddFilesButton(const SampleLibraryDataModel& sample_library)
    :AudioFileChooser(sample_library)
{
    setClickingTogglesState(false); 
}

AddFilesButton::~AddFilesButton()
{
}

void AddFilesButton::paintButton (juce::Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
    PlusButton::paintButton(g, isMouseOverButton, isButtonDown); 
}

void AddFilesButton::clicked()
{
    browseMultipleFiles(); 
}
