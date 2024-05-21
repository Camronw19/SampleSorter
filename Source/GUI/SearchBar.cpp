/*
  ==============================================================================

    SearchBar.cpp
    Created: 21 May 2024 10:46:32am
    Author:  camro

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SearchBar.h"
#include "UIConfig.h"

//==============================================================================
SearchBar::SearchBar()
    :TextEditor("SearchBar")
{
    setTextToShowWhenEmpty("Search...", juce::Colours::grey);
    setMultiLine(false); 
    setReturnKeyStartsNewLine(false);
    setFont(fonts::base); 
}

SearchBar::~SearchBar()
{
}

void SearchBar::paint (juce::Graphics& g)
{
    juce::TextEditor::paint(g);
}

void SearchBar::resized()
{
    juce::TextEditor::resized(); 
}
