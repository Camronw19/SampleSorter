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

namespace rounding
{
    static const int rounding1 = 5;
    static const int rounding2 = 10;
    static const int rounding3 = 15;
    static const int rounding4 = 20;
}

namespace AppColors
{
    namespace Dark
    {
        static const juce::Colour Primary           = juce::Colour::fromString("#FFBB86FC");
        static const juce::Colour PrimaryVarient    = juce::Colour::fromString("#FF3700B3");
        static const juce::Colour Secondary         = juce::Colour::fromString("#FF03DAC6");
        static const juce::Colour Background        = juce::Colour::fromString("#FF121212");
        static const juce::Colour Surface1dp        = juce::Colour::fromString("#0dffffff");
        static const juce::Colour Surface6dp        = juce::Colour::fromString("#1cffffff");
        static const juce::Colour Error             = juce::Colour::fromString("#FFCF6679");
        static const juce::Colour OnPrimary         = juce::Colour::fromString("#FF000000");
        static const juce::Colour OnSecondary       = juce::Colour::fromString("#FF000000");
        static const juce::Colour OnBackground      = juce::Colour::fromString("#FFFFFFFF");
        static const juce::Colour OnSurface         = juce::Colour::fromString("#FFFFFFFF");
        static const juce::Colour OnError           = juce::Colour::fromString("#FF000000");
        static const juce::Colour BackgroundFocused = juce::Colour::fromString("#1F000000");
        static const juce::Colour PrimaryFocused    = juce::Colour::fromString("#1FBB86FC");
    }

    enum ColourIds
    {
        Primary = 0x2000000,
        PrimaryVarient, 
        Secondary, 
        Background,
        Surface1dp,
        Surface6dp,
        Error, 
        OnPrimary,
        OnSecondary,
        OnBackground,
        OnSurface,
        OnError,
        BackgroundFocused, 
        PrimaryFocused,
    };
};

inline void setComponentColors(juce::LookAndFeel& look_and_feel)
{
    // TableHeaderComponent
    look_and_feel.setColour(juce::TableHeaderComponent::backgroundColourId, juce::Colours::transparentBlack);
    look_and_feel.setColour(juce::TableHeaderComponent::textColourId, look_and_feel.findColour(AppColors::OnSurface));
    look_and_feel.setColour(juce::TableHeaderComponent::ColourIds::outlineColourId, look_and_feel.findColour(AppColors::Surface6dp));
    look_and_feel.setColour(juce::TableHeaderComponent::ColourIds::highlightColourId, look_and_feel.findColour(AppColors::PrimaryFocused));

    // TableListBox
    look_and_feel.setColour(juce::TableListBox::backgroundColourId, juce::Colours::transparentBlack);

    // ScrollBar
    look_and_feel.setColour(juce::ScrollBar::ColourIds::thumbColourId, look_and_feel.findColour(AppColors::Surface6dp));
}

class DarkLookAndFeel : public juce::LookAndFeel_V4
{
public:
    DarkLookAndFeel()
    {
        // Associate each custom ColourId with its corresponding Colour
        setColour(AppColors::ColourIds::Primary,           AppColors::Dark::Primary);
        setColour(AppColors::ColourIds::PrimaryVarient,    AppColors::Dark::PrimaryVarient);
        setColour(AppColors::ColourIds::Secondary,         AppColors::Dark::Secondary);
        setColour(AppColors::ColourIds::Background,        AppColors::Dark::Background);
        setColour(AppColors::ColourIds::Surface1dp,        AppColors::Dark::Surface1dp);
        setColour(AppColors::ColourIds::Surface6dp,        AppColors::Dark::Surface6dp);
        setColour(AppColors::ColourIds::Error,             AppColors::Dark::Error);
        setColour(AppColors::ColourIds::OnPrimary,         AppColors::Dark::OnPrimary);
        setColour(AppColors::ColourIds::OnSecondary,       AppColors::Dark::OnSecondary);
        setColour(AppColors::ColourIds::OnBackground,      AppColors::Dark::OnBackground);
        setColour(AppColors::ColourIds::OnSurface,         AppColors::Dark::OnSurface);
        setColour(AppColors::ColourIds::OnError,           AppColors::Dark::OnError);
        setColour(AppColors::ColourIds::BackgroundFocused, AppColors::Dark::BackgroundFocused);
        setColour(AppColors::ColourIds::PrimaryFocused,    AppColors::Dark::PrimaryFocused);

        setComponentColors(*this); 
    }
};

