/*
  ==============================================================================

    FilterBar.cpp
    Created: 23 May 2024 8:10:34am
    Author:  camro

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterBar.h"
#include "UIConfig.h"
#include "iostream"

//==============================================================================

FilterDisplay::FilterDisplay()
{

}

FilterDisplay::~FilterDisplay()
{
}

void FilterDisplay::paint (juce::Graphics& g)
{
    g.setColour(getLookAndFeel().findColour(AppColors::Surface1dp));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), rounding::rounding1);
}

void FilterDisplay::resized()
{
}

//==============================================================================

FilterBar::FilterBar()
{
    addAndMakeVisible(m_add_filter); 
    m_add_filter.addItem("TEST", 1); 
    m_add_filter.addItem("TEST 2", 2); 

    addAndMakeVisible(m_filter_1); 
}

FilterBar::~FilterBar()
{
}

void FilterBar::paint (juce::Graphics& g)
{
    g.setColour(getLookAndFeel().findColour(AppColors::Surface1dp));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), rounding::rounding1);
}

void FilterBar::resized()
{
    auto bounds = getLocalBounds(); 
    bounds.reduce(spacing::padding1, spacing::padding1); 

    m_add_filter.setBounds(bounds.removeFromLeft(getWidth() / 4)); 
}