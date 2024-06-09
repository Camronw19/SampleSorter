/*
  ==============================================================================

    FilterBar.h
    Created: 23 May 2024 8:10:34am
    Author:  camro

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GenericComponents.h"
#include "MultiSelect.h"

//==============================================================================
/*
*/
class FilterDisplay : public juce::Component
{
public: 
    FilterDisplay(); 
    ~FilterDisplay() override; 
 
    void paint (juce::Graphics&) override;
    void resized() override;

private: 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterDisplay)
};

class FilterBar  : public juce::Component
{
public:
    FilterBar();
    ~FilterBar() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    MultiSelect m_filter_select; 
    FilterDisplay m_filter_1; 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterBar)
};

