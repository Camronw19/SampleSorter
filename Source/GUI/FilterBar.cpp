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
    : m_filter_select()
{
    addAndMakeVisible(m_filter_select); 
    m_filter_select.setButtonText("Select Filters");
    m_filter_select.addItem("Favorite", 1); 
    m_filter_select.addSeparator();
    m_filter_select.addItem("Kicks", 2); 
    m_filter_select.addItem("Snares", 3); 
    m_filter_select.addItem("Hats", 4); 
    m_filter_select.addItem("Percs", 5); 

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

    m_filter_select.setBounds(bounds.removeFromLeft(getWidth() / 4)); 
}