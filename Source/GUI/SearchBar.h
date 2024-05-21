/*
  ==============================================================================

    SearchBar.h
    Created: 21 May 2024 10:46:32am
    Author:  camro

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SearchBar  : public juce::TextEditor
{
public:
    SearchBar();
    ~SearchBar() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SearchBar)
};
