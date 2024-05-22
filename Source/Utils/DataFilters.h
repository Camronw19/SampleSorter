/*
  ==============================================================================

    DataFilters.h
    Created: 21 May 2024 3:34:17pm
    Author:  camro

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Filter
{
public: 
    virtual ~Filter() = default; 
    virtual void filter(std::shared_ptr<juce::XmlElement>& tree_to_filter, juce::String query) = 0; 
};

class FuzzySearchFilter : public Filter
{
public: 
    void filter(std::shared_ptr<juce::XmlElement>&, juce::String) override; 
};
