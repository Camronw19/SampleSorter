/*
  ==============================================================================

    Buttons.cpp
    Created: 23 May 2024 8:55:40am
    Author:  camro

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Buttons.h"
#include "UIConfig.h"

//==============================================================================
PlusButton::PlusButton()
    : juce::Button("PlusButton")
{

}

PlusButton::~PlusButton()
{
}

void PlusButton::paintButton (juce::Graphics& g, bool is_mouse_over, bool is_button_down)
{
    juce::Rectangle<int> bounds = getLocalBounds(); 

    if (is_mouse_over)
        g.setColour(getLookAndFeel().findColour(AppColors::Surface6dp)); 
    else
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

void PlusButton::resized()
{
}

//==============================================================================

AddButton::AddButton()
    : juce::Button("AddButton")
{

}

AddButton::~AddButton()
{

}

void AddButton::paintButton(juce::Graphics& g, bool is_mouse_over, bool is_button_down)
{
    juce::Rectangle<int> bounds = getLocalBounds(); 

    if (is_mouse_over)
    {
        g.setColour(getLookAndFeel().findColour(AppColors::Surface6dp)); 
        g.fillRoundedRectangle(bounds.toFloat(), rounding::rounding1); 
    }


    // Set the color for the plus sign and text
    g.setColour(getLookAndFeel().findColour(AppColors::OnBackground));

    // Calculate the bounds for the plus sign and text
    int padding = spacing::padding1;
    int plus_size = bounds.getHeight() / 2;
    int plus_thickness= 2;

    // Draw the plus sign
    juce::Path plusPath;
    plusPath.startNewSubPath(padding, bounds.getCentreY());
    plusPath.lineTo(padding + plus_size, bounds.getCentreY());
    plusPath.startNewSubPath(padding + plus_size / 2, bounds.getCentreY() - plus_size / 2);
    plusPath.lineTo(padding + plus_size / 2, bounds.getCentreY() + plus_size / 2);

    g.strokePath(plusPath, juce::PathStrokeType(plus_thickness));

    // Draw the text
    juce::Font font(fonts::base); 
    g.setFont(font);

    // Calculate the area available for text
    int textStartX = padding + plus_size + padding;
    int textWidth = bounds.getWidth() - textStartX - padding;

    if (g.getCurrentFont().getStringWidth(m_text) <= textWidth)
        g.drawText(m_text, textStartX, 0, textWidth, bounds.getHeight(), juce::Justification::centredLeft);

    }

void AddButton::resized()
{

}

void AddButton::setText(const juce::String text)
{
    m_text = text; 
}

