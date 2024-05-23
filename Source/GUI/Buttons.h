/*
  ==============================================================================

    Buttons.h
    Created: 23 May 2024 8:55:40am
    Author:  camro

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PlusButton : public juce::Button
{
public:
    PlusButton();
    ~PlusButton() override;

    void paintButton (juce::Graphics&, bool, bool) override;
    void resized() override;


private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlusButton)
};

class AddButton : public juce::Button
{
public: 
    AddButton(); 
    ~AddButton() override; 

    void paintButton (juce::Graphics&, bool, bool) override;
    void resized() override;

    void setText(const juce::String); 

private:
    juce::String m_text; 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AddButton)
};
