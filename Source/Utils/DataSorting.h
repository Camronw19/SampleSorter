/*
  ==============================================================================

    DataSorting.h
    Created: 16 May 2024 12:25:48pm
    Author:  camro

  ==============================================================================
*/

#pragma once
#include "DataSorting.h"
#include <JuceHeader.h>

class CompareNaturalStringSorter
{
public:
    CompareNaturalStringSorter(const juce::String&, const juce::String&, bool); 

    int compareElements(juce::XmlElement*, juce::XmlElement*);

private:
    juce::String m_attribute_to_sort;
    juce::String m_defualt_attribute_to_sort; 
    int m_direction;
};
