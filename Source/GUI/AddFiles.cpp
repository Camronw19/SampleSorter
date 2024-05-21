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
    :AudioFileChooser(sample_library), 
    juce::Button("AddFilesButton")
{
    setClickingTogglesState(false); 
}

AddFilesButton::~AddFilesButton()
{
}

void AddFilesButton::paintButton (juce::Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
    juce::Rectangle<int> bounds = getLocalBounds(); 

    g.setColour(getLookAndFeel().findColour(AppColors::Surface1dp)); 
    g.fillRoundedRectangle(bounds.toFloat(), rounding::rounding1); 
    
    // Draw add icon
    int center_x = bounds.getCentreX();
    int center_y = bounds.getCentreY();

    const int width = 20; 
    const int height = 2; 

    g.setColour(getLookAndFeel().findColour(AppColors::Secondary)); 

    // Draw the horizontal line
    g.fillRect(center_x - width / 2, center_y - height/ 2, width, height);

    // Draw the vertical line
    g.fillRect(center_x - height / 2, center_y - width / 2, height, width);
}

void AddFilesButton::clicked()
{
    browseMultipleFiles(); 
}
