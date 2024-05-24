/*
  ==============================================================================

    Icons.cpp
    Created: 24 May 2024 7:55:00am
    Author:  camro

  ==============================================================================
*/

#include "Icons.h"
#include "UIConfig.h"

std::unique_ptr<juce::DrawablePath> createFilterIcon()
{
    // Create a DrawablePath object to hold our icon's path
    auto drawable_path = std::make_unique<juce::DrawablePath>();
    juce::Path path; 

    // Define the bar heights and initial width
    float bar_height = 7.5f;
    float initial_width = 100.0f;
    float width_decrement = 30.0f;
    float gap = 20.0f;
    float y = 0.0f;
    float x = 0.0f;

    // Add the three bars to the path
    for (int i = 0; i < 3; ++i)
    {
        float currentWidth = initial_width - (i * width_decrement);
        float x = (i * width_decrement) / 2; 
        path.addRectangle(x, y, currentWidth, bar_height);
        y += bar_height + gap;
    }

    // Set the path and color of drawable
    drawable_path->setPath(path);
    drawable_path->setFill(drawable_path->getLookAndFeel().findColour(AppColors::OnBackground));

    return drawable_path;
}
