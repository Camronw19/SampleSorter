/*
  ==============================================================================

    UIConfig.h
    Created: 14 May 2024 3:36:32pm
    Author:  camro

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace spacing
{
    static const int padding1 = 5;
    static const int padding2 = 10;
    static const int padding3 = 15;
    static const int padding4 = 20;
};

namespace AppColors
{
    namespace Dark
    {
        static const juce::Colour Primary        = juce::Colour::fromString("#FFBB86FC");
        static const juce::Colour PrimaryVarient = juce::Colour::fromString("#FF3700B3");
        static const juce::Colour Secondary      = juce::Colour::fromString("#FF03DAC6");
        static const juce::Colour Background     = juce::Colour::fromString("#FF121212");
        static const juce::Colour Surface        = juce::Colour::fromFloatRGBA(1.0f, 1.0f, 1.0f, 0.05f);
        static const juce::Colour Error          = juce::Colour::fromString("#FFCF6679");
        static const juce::Colour OnPrimary      = juce::Colour::fromString("#FF000000");
        static const juce::Colour OnSecondary    = juce::Colour::fromString("#FF000000");
        static const juce::Colour OnBackground   = juce::Colour::fromString("#FFFFFFFF");
        static const juce::Colour OnSurface      = juce::Colour::fromString("#FFFFFFFF");
        static const juce::Colour OnError        = juce::Colour::fromString("#FF000000");
    }

    enum ColourIds
    {
        Primary = 0x2000000,
        PrimaryVarient, 
        Secondary, 
        Background,
        Surface, 
        Error, 
        OnPrimary,
        OnSecondary,
        OnBackground,
        OnSurface,
        OnError
    };
};

class DarkLookAndFeel : public juce::LookAndFeel_V4
{
public:
    DarkLookAndFeel()
    {
        // Associate each custom ColourId with its corresponding Colour
        setColour(AppColors::ColourIds::Primary,        AppColors::Dark::Primary);
        setColour(AppColors::ColourIds::PrimaryVarient, AppColors::Dark::PrimaryVarient);
        setColour(AppColors::ColourIds::Secondary,      AppColors::Dark::Secondary);
        setColour(AppColors::ColourIds::Background,     AppColors::Dark::Background);
        setColour(AppColors::ColourIds::Surface,        AppColors::Dark::Surface);
        setColour(AppColors::ColourIds::Error,          AppColors::Dark::Error);
        setColour(AppColors::ColourIds::OnPrimary,      AppColors::Dark::OnPrimary);
        setColour(AppColors::ColourIds::OnSecondary,    AppColors::Dark::OnSecondary);
        setColour(AppColors::ColourIds::OnBackground,   AppColors::Dark::OnBackground);
        setColour(AppColors::ColourIds::OnSurface,      AppColors::Dark::OnSurface);
        setColour(AppColors::ColourIds::OnError,        AppColors::Dark::OnError);
    }
};

