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
    inline const int padding1 = 5;
    inline const int padding2 = 10;
    inline const int padding3 = 15;
    inline const int padding4 = 20;
};

namespace rounding
{
    inline const int rounding1 = 5;
    inline const int rounding2 = 10;
    inline const int rounding3 = 15;
    inline const int rounding4 = 20;
}

namespace fonts
{
    inline const float base = 14.0f; 
}

namespace AppColors
{
    namespace Dark
    {
        inline const juce::Colour Primary           = juce::Colour::fromString("#FFBB86FC");
        inline const juce::Colour PrimaryVarient    = juce::Colour::fromString("#FF3700B3");
        inline const juce::Colour Secondary         = juce::Colour::fromString("#FF03DAC6");
        inline const juce::Colour Background        = juce::Colour::fromString("#FF121212");
        inline const juce::Colour Surface1dp        = juce::Colour::fromString("#0dffffff");
        inline const juce::Colour Surface6dp        = juce::Colour::fromString("#1cffffff");
        inline const juce::Colour Error             = juce::Colour::fromString("#FFCF6679");
        inline const juce::Colour OnPrimary         = juce::Colour::fromString("#FF000000");
        inline const juce::Colour OnSecondary       = juce::Colour::fromString("#FF000000");
        inline const juce::Colour OnBackground      = juce::Colour::fromString("#FFFFFFFF");
        inline const juce::Colour OnSurface         = juce::Colour::fromString("#FFFFFFFF");
        inline const juce::Colour OnError           = juce::Colour::fromString("#FF000000");
        inline const juce::Colour BackgroundFocused = juce::Colour::fromString("#1F000000");
        inline const juce::Colour PrimaryFocused    = juce::Colour::fromString("#1FBB86FC");
    }

    namespace Light
    {
        inline const juce::Colour Primary           = juce::Colour::fromString("#FF6200EE");
        inline const juce::Colour PrimaryVarient    = juce::Colour::fromString("#FF3700B3");
        inline const juce::Colour Secondary         = juce::Colour::fromString("#FF03DAC6");
        inline const juce::Colour Background        = juce::Colour::fromString("#FFFFFFFF");
        inline const juce::Colour Surface1dp        = juce::Colour::fromString("#0d000000");
        inline const juce::Colour Surface6dp        = juce::Colour::fromString("#1cFFFFFF");
        inline const juce::Colour Error             = juce::Colour::fromString("#FFB00020");
        inline const juce::Colour OnPrimary         = juce::Colour::fromString("#FFFFFFFF");
        inline const juce::Colour OnSecondary       = juce::Colour::fromString("#FF000000");
        inline const juce::Colour OnBackground      = juce::Colour::fromString("#FF000000");
        inline const juce::Colour OnSurface         = juce::Colour::fromString("#FF000000");
        inline const juce::Colour OnError           = juce::Colour::fromString("#FFFFFFFF");
        inline const juce::Colour BackgroundFocused = juce::Colour::fromString("#1FFFFFFF");
        inline const juce::Colour PrimaryFocused    = juce::Colour::fromString("#1F6200EE");
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

    // TextEditor
    look_and_feel.setColour(juce::TextEditor::ColourIds::backgroundColourId, look_and_feel.findColour(AppColors::Surface1dp));
    look_and_feel.setColour(juce::TextEditor::ColourIds::focusedOutlineColourId, juce::Colours::transparentBlack);
    look_and_feel.setColour(juce::TextEditor::ColourIds::highlightColourId, look_and_feel.findColour(AppColors::PrimaryFocused));
    look_and_feel.setColour(juce::TextEditor::ColourIds::highlightedTextColourId, look_and_feel.findColour(AppColors::Primary));
    look_and_feel.setColour(juce::TextEditor::ColourIds::outlineColourId, juce::Colours::transparentBlack);
    look_and_feel.setColour(juce::TextEditor::ColourIds::shadowColourId, look_and_feel.findColour(AppColors::Surface1dp));
    look_and_feel.setColour(juce::TextEditor::ColourIds::textColourId, look_and_feel.findColour(AppColors::OnBackground));
    look_and_feel.setColour(juce::CaretComponent::caretColourId, look_and_feel.findColour(AppColors::Secondary)); 

    // ComboBox
    look_and_feel.setColour(juce::ComboBox::ColourIds::backgroundColourId, look_and_feel.findColour(AppColors::Surface1dp)); 
    look_and_feel.setColour(juce::ComboBox::ColourIds::arrowColourId, look_and_feel.findColour(AppColors::Secondary)); 
    look_and_feel.setColour(juce::ComboBox::ColourIds::buttonColourId, look_and_feel.findColour(AppColors::Primary)); 
    look_and_feel.setColour(juce::ComboBox::ColourIds::focusedOutlineColourId, look_and_feel.findColour(AppColors::Surface1dp)); 
    look_and_feel.setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colours::transparentBlack); 
    look_and_feel.setColour(juce::ComboBox::ColourIds::textColourId, look_and_feel.findColour(AppColors::OnBackground)); 

    // PopupMenu
    look_and_feel.setColour(juce::PopupMenu::ColourIds::backgroundColourId, juce::Colour::fromString("#FE292929"));
    look_and_feel.setColour(juce::PopupMenu::ColourIds::headerTextColourId, look_and_feel.findColour(AppColors::OnBackground)); 
    look_and_feel.setColour(juce::PopupMenu::ColourIds::highlightedBackgroundColourId, look_and_feel.findColour(AppColors::PrimaryFocused)); 
    look_and_feel.setColour(juce::PopupMenu::ColourIds::highlightedTextColourId, look_and_feel.findColour(AppColors::Primary)); 
    look_and_feel.setColour(juce::PopupMenu::ColourIds::textColourId, look_and_feel.findColour(AppColors::OnBackground)); 

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

    // TableListBox
    void drawTableHeaderColumn(juce::Graphics& g, juce::TableHeaderComponent& header,
        const juce::String& columnName, int /*columnId*/,
        int width, int height, bool isMouseOver, bool isMouseDown,
        int columnFlags) override
    {
        auto highlightColour = header.findColour(juce::TableHeaderComponent::highlightColourId);

        if (isMouseDown)
            g.fillAll(highlightColour);
        else if (isMouseOver)
            g.fillAll(highlightColour.withMultipliedAlpha(0.625f));

        juce::Rectangle<int> area(width, height);
        area.reduce(4, 0);

        if ((columnFlags & (juce::TableHeaderComponent::sortedForwards | juce::TableHeaderComponent::sortedBackwards)) != 0)
        {
            juce::Path sortArrow;
            sortArrow.addTriangle(0.0f, 0.0f,
                0.5f, (columnFlags & juce::TableHeaderComponent::sortedForwards) != 0 ? -0.8f : 0.8f,
                1.0f, 0.0f);

            g.setColour(findColour(AppColors::OnBackground));
            g.fillPath(sortArrow, sortArrow.getTransformToScaleToFit(area.removeFromRight(height / 2).reduced(2).toFloat(), true));
        }

        g.setColour(header.findColour(juce::TableHeaderComponent::textColourId));
        g.setFont(juce::Font((float)height * 0.5f, juce::Font::bold));
        g.drawFittedText(columnName, area, juce::Justification::centredLeft, 1);
    }

    // TextEditor 
void fillTextEditorBackground (juce::Graphics& g, int width, int height, juce::TextEditor& textEditor) override
{
    if (dynamic_cast<juce::AlertWindow*> (textEditor.getParentComponent()) != nullptr)
    {
        g.setColour (textEditor.findColour (juce::TextEditor::backgroundColourId));
        g.fillRoundedRectangle(0, 0, width, height, rounding::rounding1); 

        g.setColour (textEditor.findColour (juce::TextEditor::outlineColourId));
        g.drawHorizontalLine (height - 1, 0.0f, static_cast<float> (width));
    }
    else
    {
        g.setColour (textEditor.findColour (juce::TextEditor::backgroundColourId));
        g.fillRoundedRectangle(0, 0, width, height, rounding::rounding1); 
    }
}

};

class LightLookAndFeel : public juce::LookAndFeel_V4
{
public:
    LightLookAndFeel()
    {
        // Associate each custom ColourId with its corresponding Colour
        setColour(AppColors::ColourIds::Primary,           AppColors::Light::Primary);
        setColour(AppColors::ColourIds::PrimaryVarient,    AppColors::Light::PrimaryVarient);
        setColour(AppColors::ColourIds::Secondary,         AppColors::Light::Secondary);
        setColour(AppColors::ColourIds::Background,        AppColors::Light::Background);
        setColour(AppColors::ColourIds::Surface1dp,        AppColors::Light::Surface1dp);
        setColour(AppColors::ColourIds::Surface6dp,        AppColors::Light::Surface6dp);
        setColour(AppColors::ColourIds::Error,             AppColors::Light::Error);
        setColour(AppColors::ColourIds::OnPrimary,         AppColors::Light::OnPrimary);
        setColour(AppColors::ColourIds::OnSecondary,       AppColors::Light::OnSecondary);
        setColour(AppColors::ColourIds::OnBackground,      AppColors::Light::OnBackground);
        setColour(AppColors::ColourIds::OnSurface,         AppColors::Light::OnSurface);
        setColour(AppColors::ColourIds::OnError,           AppColors::Light::OnError);
        setColour(AppColors::ColourIds::BackgroundFocused, AppColors::Light::BackgroundFocused);
        setColour(AppColors::ColourIds::PrimaryFocused,    AppColors::Light::PrimaryFocused);

        setComponentColors(*this); 
    }

    void drawTableHeaderColumn(juce::Graphics& g, juce::TableHeaderComponent& header,
        const juce::String& columnName, int /*columnId*/,
        int width, int height, bool isMouseOver, bool isMouseDown,
        int columnFlags) 
    {
        auto highlightColour = header.findColour(juce::TableHeaderComponent::highlightColourId);

        if (isMouseDown)
            g.fillAll(highlightColour);
        else if (isMouseOver)
            g.fillAll(highlightColour.withMultipliedAlpha(0.625f));

        juce::Rectangle<int> area(width, height);
        area.reduce(4, 0);

        if ((columnFlags & (juce::TableHeaderComponent::sortedForwards | juce::TableHeaderComponent::sortedBackwards)) != 0)
        {
            juce::Path sortArrow;
            sortArrow.addTriangle(0.0f, 0.0f,
                0.5f, (columnFlags & juce::TableHeaderComponent::sortedForwards) != 0 ? -0.8f : 0.8f,
                1.0f, 0.0f);

            g.setColour(findColour(AppColors::OnBackground));
            g.fillPath(sortArrow, sortArrow.getTransformToScaleToFit(area.removeFromRight(height / 2).reduced(2).toFloat(), true));
        }

        g.setColour(header.findColour(juce::TableHeaderComponent::textColourId));
        g.setFont(juce::Font((float)height * 0.5f, juce::Font::bold));
        g.drawFittedText(columnName, area, juce::Justification::centredLeft, 1);
    }
};


